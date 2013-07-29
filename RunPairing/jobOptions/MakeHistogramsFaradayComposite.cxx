 int MakeHistogramsFaradayComposite ( const std::string& inputDirs,
                                      const std::string& compositeName,
                                      const std::string& submitDir,
                                      const std::string& ilumiCalcFile )
{
  // Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  // Output name
  std::string outputName = "output";

  // Create a new SampleHandler to grab all samples
  SH::SampleHandler sh;

  // Add periods to sample for processing
  std::stringstream inputStringStream(inputDirs);
  std::string temp;
  while(std::getline(inputStringStream, temp, ','))
  {
    SH::scanDir (sh, temp);
  }

  sh.setMetaString ("nc_tree", "physics");

  // Create a new job
  EL::Job job;
  job.sampleHandler (sh);

  // Create and Output Stream and add to job
  EL::OutputStream output (outputName);
  job.outputAdd (output);

  // Add MiniNtupleMaker algorithm to job
  HistogramFactory *histoFactory = new HistogramFactory;
  histoFactory->outputName = outputName;

  std::string RootCoreDir = getenv("ROOTCOREDIR");
  std::string dataDir = RootCoreDir  + "/data/";

  std::string sliceDir = dataDir + "MuonEfficiency/";

  TnPSlices slices;
  slices.AddSlices("pt", sliceDir + "pt.txt");
  slices.AddSlices("eta", sliceDir + "eta.txt");
  slices.AddSlices("phi", sliceDir + "phi.txt");
  slices.AddSlices("etcone20", sliceDir + "etcone20.txt");
  slices.AddSlices("etcone30", sliceDir + "etcone30.txt");
  slices.AddSlices("etcone40", sliceDir + "etcone40.txt");
  slices.AddSlices("ptcone20", sliceDir + "ptcone20.txt");
  slices.AddSlices("ptcone30", sliceDir + "ptcone30.txt");
  slices.AddSlices("ptcone40", sliceDir + "ptcone40.txt");
  slices.AddSlices("nucone20", sliceDir + "nucone20.txt");
  slices.AddSlices("nucone30", sliceDir + "nucone30.txt");
  slices.AddSlices("jetDr", sliceDir + "jetDr.txt");
  slices.AddSlices("nucone40", sliceDir + "nucone40.txt");
  slices.Initialize();

  /// Initialize and configure Tag Selector
  TJPsiTagSelector* tagSelector = new TJPsiTagSelector();
  tagSelector->etaCut = 2.5; tagSelector->combinedMuonCut = 1;
  tagSelector->ptCut = 4000; tagSelector->d0Cut = 0.3;
  tagSelector->z0Cut = 1.5; tagSelector->d0SigCut = 3.0;
  tagSelector->z0SigCut = 3.0;

  /// Configure probe
  TJPsiProbeSelector* probeSelector = new TJPsiProbeSelector();
  probeSelector->etaCut = 2.5; probeSelector->pCut = 3000;

  /// Configure pair
  TJPsiPairSelector* pairSelector = new TJPsiPairSelector();
  pairSelector->deltaRCutMax = 3.5; pairSelector->signCut = -1;
  pairSelector->deltaRCutMin = 0.2;
  pairSelector->minMassCut = 2000.; pairSelector->maxMassCut = 4000.;
  pairSelector->deltaZ0Cut = 2.;

  /// Configure muon probe selector
  TJPsiMuonProbeSelector* muonProbeSelector = new TJPsiMuonProbeSelector();
  muonProbeSelector->deltaRCut = 0.001;

  TJPsiSMTSelector* smtSelector = new TJPsiSMTSelector();
  smtSelector->d0Cut = 3;
  smtSelector->z0SinCut = 3;
  smtSelector->chi2Cut = 3.2;

  /// Configure MCP selector
  TMCPSelector* mcpSelector = new TMCPSelector();

  /// Jet selector
  TJetSelector* jetSelector = new TJetSelector();
  jetSelector->isBadLooseMinusCut = 1;
  jetSelector->emfracCut = 0.8;
  jetSelector->nTrkCut = 3;

  std::cout << "Setting up classifier" << std::endl;
  TJPsiClassifier* jpsiClassifier = new TJPsiClassifier();
  jpsiClassifier->tagSelector = tagSelector;
  jpsiClassifier->pairSelector = pairSelector;
  jpsiClassifier->probeSelector = probeSelector;
  jpsiClassifier->muonProbeSelector = muonProbeSelector;
  jpsiClassifier->smtSelector = smtSelector;
  jpsiClassifier->mcpSelector = mcpSelector;

  // Event Weighting object
  EventWeighting* eventWgt = new EventWeighting("NOMINAL");
  Root::TPileupReweighting* pileupTool = new Root::TPileupReweighting("pileup");
  pileupTool->AddConfigFile("$ROOTCOREDIR/data/PileupReweighting/mc12_jpsi_config.prw.root");
  

  // used to fix expected Nvtx discrepancy between MC and data due to z beam spot size
  bool runKFactorCorrection = false;
  if(runKFactorCorrection != false) pileupTool->SetDataScaleFactors(1./1.11);

  pileupTool->AddLumiCalcFile(ilumiCalcFile.c_str());
  pileupTool->SetUnrepresentedDataAction(2);
  pileupTool->Initialize();

  eventWgt->AddWeighting(new PileupReWeighting("PRW", "Pileup Reweighting Tool", pileupTool)); // PRW tool

  std::cout << "Adding slices" << std::endl;
  histoFactory->varSlices = slices;
  histoFactory->jpsiClassifier = jpsiClassifier;
  histoFactory->jetSelector = jetSelector;
  histoFactory->eventWgt = eventWgt;

  /// Set the number of events to print full debug information for
  histoFactory->nDebugEvents = 10;
  job.algsAdd(histoFactory);
  
  // Setup some shell init info
  std::string optionMergeLogs = "-j oe";
  std::string optionQueue = "-q long";
  std::string option = optionMergeLogs + " " + optionQueue;
  
  std::string shellInitCmd = "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase && source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh && eval localSetupROOT --skipConfirm --rootVersion=\"5.30.06-x86_64-slc5-gcc4.3\"  && echo setup success || echo setup failure; which root; echo $PATH";
  std::cout << "Submitting with init command: " << shellInitCmd << std::endl;
  std::cout << "Options for submission: " << option << std::endl;

  // Create a new driver
  EL::TorqueDriver driver;
  driver.shellInit = shellInitCmd;
  
  job.options()->setDouble(EL::Job::optFilesPerWorker, 10);
  job.options()->setString(EL::Job::optSubmitFlags, option);

  std::cout << "Submitting" << std::endl;

  // process the job using the driver
  driver.submitOnly (job, submitDir);
}
