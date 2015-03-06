void MakeKinematicsFaraday(const std::string& inputDir,
                           const std::string& submitDir,
                           const std::string& lumiCalcFile = "ilumicalc_histograms_AllPeriodData12.root",
                           int doPU = 0) {
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  std::string outputName = "output";

  submitDir.append("_faraday");

  // Create a new SampleHandler to grab all samples
  SH::SampleHandler sh;
  SH::scanDir(sh, inputDir);
  sh.setMetaString ("nc_tree", "physics");

  // Create a new job
  EL::Job job;
  job.sampleHandler (sh);

  // Create and Output Stream and add to job
  EL::OutputStream output (outputName);
  job.outputAdd (output);

  // Add MiniNtupleMaker algorithm to job
  SampleHistograms *sampleHistograms = new SampleHistograms;
  sampleHistograms->outputName = outputName;

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
  pairSelector->deltaZ0Cut = 2;

  /// Configure muon probe selector
  TJPsiMuonProbeSelector* muonProbeSelector = new TJPsiMuonProbeSelector();
  muonProbeSelector->deltaRCut = 0.001;

  TJPsiSMTSelector* smtSelector = new TJPsiSMTSelector();
  smtSelector->d0Cut = 3;
  smtSelector->z0SinCut = 3;
  smtSelector->chi2Cut = 3.2;

  /// Configure MCP selector
  TMCPSelector* mcpSelector = new TMCPSelector();
  
  std::cout << "Setting up classifier" << std::endl;
  TJPsiClassifier* jpsiClassifier = new TJPsiClassifier();
  jpsiClassifier->tagSelector = tagSelector;
  jpsiClassifier->pairSelector = pairSelector;
  jpsiClassifier->probeSelector = probeSelector;
  jpsiClassifier->muonProbeSelector = muonProbeSelector;
  jpsiClassifier->smtSelector = smtSelector;
  jpsiClassifier->mcpSelector = mcpSelector;

  std::cout << "Setting up pileup tool" << std::endl;
  Root::TPileupReweighting* pileupTool = new Root::TPileupReweighting("pileup");
  pileupTool->AddConfigFile("$ROOTCOREDIR/data/PileupReweighting/mc12_jpsi_config.prw.root");
  // pileupTool->SetDataScaleFactors(1./1.11);
  pileupTool->AddLumiCalcFile(lumiCalcFile);
  pileupTool->Initialize();

  // Configure weighting files
  std::cout << "Setting up event weight object" << std::endl;
  EventWeighting* eventWgt = new EventWeighting("NOMINAL");
  eventWgt->AddWeighting(new PileupReWeighting("PRW", "Pileup Reweighting Tool", pileupTool));

  sampleHistograms->jpsiClassifier = jpsiClassifier;
  sampleHistograms->eventWgt = eventWgt;
  sampleHistograms->doPU = doPU;
  sampleHistograms->highCut = 15;
  sampleHistograms->lowCut = 10;

  /// Set the number of events to print full debug information for
  job.algsAdd(sampleHistograms);
  sampleHistograms->nDebugEvents = 1000;

  std::cout << "Driver" << std::endl;
  
  std::string optionMergeLogs = "-j oe";
  std::string optionQueue = "-q long ";
  std::string option = optionMergeLogs + " " + optionQueue;

  std::cout << "Options for submission: " << option << std::endl;

  EL::TorqueDriver driver;
  driver.shellInit = "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase && source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh && eval localSetupROOT --skipConfirm --rootVersion=\"5.30.06-x86_64-slc5-gcc4.3\"  && echo setup success || echo setup failure; which root; which root.exe; echo $PATH; cat /etc/redhat-release";
  
  job.options()->setString(EL::Job::optSubmitFlags, option);
  job.options()->setDouble(EL::Job::optFilesPerWorker, 10);
  

  std::cout << "Submitting" << std::endl;

  // process the job using the driver
  driver.submitOnly (job, submitDir);
}
