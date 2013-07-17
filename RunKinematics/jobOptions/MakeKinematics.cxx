void MakeKinematics (const std::string& inputDir,
                     const std::string& submitDir,
                     const std::string& lumiCalcFile="ilumicalc_histograms_AllPeriodData12.root",
                     const int& doPU=0,
                     const float& maxEvents=0)
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
  SampleHistograms *sampleHistograms = new SampleHistograms;
  sampleHistograms->outputName = outputName;

  /// Initialize and configure Tag Selector
  TJPsiTagSelector* tagSelector = new TJPsiTagSelector();
  tagSelector->etaCut = 2.5; tagSelector->combinedMuonCut = 1;
  tagSelector->ptCut = 4000; 
  tagSelector->d0Cut = 0.3; tagSelector->d0SigCut = 3.0;
  tagSelector->z0Cut = 1.5; tagSelector->z0SigCut = 3.0;
  
  /// Configure probe
  TJPsiProbeSelector* probeSelector = new TJPsiProbeSelector();
  probeSelector->etaCut = 2.5; probeSelector->pCut = 4000;

  /// Configure pair
  TJPsiPairSelector* pairSelector = new TJPsiPairSelector();
  pairSelector->signCut = -1;
  pairSelector->deltaRCutMin = 0.2; pairSelector->deltaRCutMax = 3.5;
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
  if(maxEvents != 0)
  {
    job.options()->setDouble (EL::Job::optMaxEvents, maxEvents);
  }

  std::cout << "Driver" << std::endl;

  // Create a new driver
  EL::DirectDriver driver;

  // process the job using the driver
  driver.submit (job, submitDir);
}
