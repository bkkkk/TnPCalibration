 MakeHistograms ( const std::string& inputDir,
                  const std::string& submitDir,
                  const std::string& ilumiCalcFile="$ROOTCOREDIR/data/PileupReweighting/ilumicalc_histograms_PeriodA.root" )
{
  // Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  // Output name
  std::string outputName = "output";

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
  HistogramFactory *histoFactory = new HistogramFactory;
  histoFactory->outputName = outputName;

  std::string RootCoreDir = getenv("ROOTCOREDIR");
  std::string dataDir = RootCoreDir  + "/data/";

  std::string sliceDir = dataDir + "MuonEfficiency/";

  /// Weighting
  Root::TPileupReweighting* pileupTool = new Root::TPileupReweighting("pileup");
  pileupTool->AddConfigFile("$ROOTCOREDIR/data/PileupReweighting/mc12_jpsi_config.prw.root");
  // pileupTool->SetDataScaleFactors(1./1.11);
  pileupTool->AddLumiCalcFile(ilumiCalcFile.c_str());
  pileupTool->SetUnrepresentedDataAction(2);

  pileupTool->Initialize();

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
  eventWgt->AddWeighting(new PileupReWeighting("PRW", "Pileup Reweighting Tool", pileupTool)); // PRW tool

  std::cout << "Adding slices" << std::endl;
  histoFactory->pileupTool = pileupTool;
  histoFactory->varSlices = slices;
  histoFactory->jpsiClassifier = jpsiClassifier;
  histoFactory->jetSelector = jetSelector;
  histoFactory->eventWgt = eventWgt;

  /// Set the number of events to print full debug information for
  histoFactory->nDebugEvents = 10;
  job.algsAdd(histoFactory);
  
  job.options()->setDouble (EL::Job::optMaxEvents, 100000);
  
  // Create a new driver
  EL::DirectDriver driver;

  // Submitting
  std::cout << "Submitting" << std::endl;

  // process the job using the driver
  driver.submit (job, submitDir);
}
