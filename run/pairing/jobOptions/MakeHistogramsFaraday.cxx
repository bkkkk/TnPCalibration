 MakeHistogramsFaraday ( const std::string& processingTag,
                         const std::string& inputSample,
                         const std::string& label,
                         const std::string& periodForPrw="None")
{
  // Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  std::string sep = std::string(80, '=') + "\n";

  // Output name
  std::string outputName = "output";

  std::string batchName = "Batch-";
  batchName.append(processingTag);

  std::stringstream fullPath;
  fullPath << "/scratch3/jblanco/SMTMiniNtuples/SkimDB-" << batchName << ".xml";

  std::cout << sep << " Processing Sample: " << inputSample
            << " from: " << processingTag << "\n" << sep;

  std::cout << " Loading Skims DB : " << fullPath.str() << std::endl;

  Skimming::SkimListReader* skimList = new Skimming::SkimListReader(fullPath.str(), batchName);
  std::string inputDir = skimList->GetPeriodPath(inputSample);
  std::cout << " Running over: " << inputDir << std::endl;

  // Event Weighting object
  EventWeighting* eventWgt = new EventWeighting("NOMINAL");

  // Testing PRW disabled for now
#ifdef DOPRW
  std::cout << "!!!!! WARNING !!!!! RUNNING WITH PRW DISABLED !!!!!! WARNING !!!!!!!" << std::endl;
#endif
  // Do PRW for MC only
  bool isMC = false;
  if(TString(inputSample).Contains("JPsi") && TString(periodForPrw).Contains("None") != true)
  {
    isMC = true;
    
    std::string prwSharePath = gSystem->ExpandPathName("$ROOTCOREDIR/data/PileupReweighting/");
    std::stringstream prwConfigDBFullPath;          
    prwConfigDBFullPath << prwSharePath << "SkimDB-" << processingTag << ".xml";
    std::cout << sep << " Running on MC, loading PRW configuration DB from: "
              << prwConfigDBFullPath.str() << std::endl;
    
    Skimming::SkimListReader* prwConfiguration = new Skimming::SkimListReader(prwConfigDBFullPath.str(), processingTag);
    std::string prwFullPath = prwConfiguration->GetPeriodPath(inputSample);
    std::string ilumiCalcFile = prwConfiguration->GetPeriodPath(periodForPrw);

    std::cout << " Loading PRW configuration file " << prwFullPath << std::endl;
    std::cout << " Loading iLumiCalc file: " << ilumiCalcFile << std::endl;
    

    Root::TPileupReweighting* pileupTool = new Root::TPileupReweighting("pileup");
    pileupTool->AddConfigFile(prwFullPath.c_str());
  
    // used to fix expected Nvtx discrepancy between MC and data due to z beam spot size
#ifdef DO_NVTX_FIX
    std::cout << "Running with scale factor Nvtx correction" << std::endl;
    pileupTool->SetDataScaleFactors(1./1.11);
#endif

    pileupTool->AddLumiCalcFile(ilumiCalcFile.c_str());
    pileupTool->SetUnrepresentedDataAction(2);
    pileupTool->Initialize();

    double override = 0;

    std::cout << "!!! Running in Channel override mode !!!" << std::endl;
    if(TString(inputSample).Contains("NonPromptJPsi")) {
      override = 208202;
    } else {
      override = 208002;
    }

    eventWgt->AddWeighting(new PileupReWeighting("PRW", "Pileup Reweighting Tool", pileupTool, override)); // PRW tool
  }
  std::cout << sep;

  // Create a new SampleHandler to grab all samples
  SH::SampleHandler sh;
  SH::scanDir(sh, inputDir);
  sh.print();
  sh.setMetaString ("nc_tree", "physics");
  sh.setMetaString ("inputSample", inputSample);
  sh.setMetaString ("processingTag", processingTag);

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

  /// Initialize and configure Tag selector
  TJPsiTagSelector* tagSelector = new TJPsiTagSelector();
  tagSelector->etaCut = 2.5;
  tagSelector->combinedMuonCut = 1;
  tagSelector->ptCut = 4000;
  tagSelector->d0Cut = 0.3; tagSelector->d0SigCut = 3.0;
  tagSelector->z0Cut = 1.5; tagSelector->z0SigCut = 3.0;

  /// Configure probe
  
  TJPsiProbeSelector* probeSelector = new TJPsiProbeSelector();
  probeSelector->etaCut = 2.5; probeSelector->pCut = 4000;
  if(probeSelector->pCut != 3000)
  {
    std::cout << "!!!!! WARNING !!!!! Running with probe pT cut : "
              << probeSelector->pCut << std::endl;
  }

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

  std::cout << " Setting up classifier" << std::endl;
  TJPsiClassifier* jpsiClassifier = new TJPsiClassifier();
  jpsiClassifier->tagSelector = tagSelector;
  jpsiClassifier->pairSelector = pairSelector;
  jpsiClassifier->probeSelector = probeSelector;
  jpsiClassifier->muonProbeSelector = muonProbeSelector;
  jpsiClassifier->smtSelector = smtSelector;
  jpsiClassifier->mcpSelector = mcpSelector;
  std::cout << sep;

  std::cout << " Setting up analysis components" << std::endl;
  histoFactory->varSlices = slices;
  histoFactory->jpsiClassifier = jpsiClassifier;
  histoFactory->jetSelector = jetSelector;
  histoFactory->eventWgt = eventWgt;
  std::cout << sep;

  /// Set the number of events to print full debug information for
  histoFactory->nDebugEvents = 10;
  job.algsAdd(histoFactory);
  
  // Setup some shell init info
  std::string optionMergeLogs = "-j oe";
  std::string optionQueue = "-q long";
  std::string option = optionMergeLogs + " " + optionQueue;
  
  std::string shellInitCmd = "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase && source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh && eval localSetupROOT --skipConfirm && echo setup success || echo setup failure; which root; echo $PATH";

  // Create a new driver
  EL::TorqueDriver driver;
  driver.shellInit = shellInitCmd;
  
  job.options()->setDouble(EL::Job::optFilesPerWorker, 10);
  job.options()->setString(EL::Job::optSubmitFlags, option);

  std::cout << "Submitting" << std::endl;

  TDatime temp;
  std::stringstream datime;
  datime << temp.GetDate() << temp.GetTime();


  std::string basePath = "/scratch3/jblanco/CalibrationHistograms/";
  std::stringstream submitDir;

  submitDir << basePath << "CalibSample-" << processingTag << "_" << inputSample << "-"; 

  if (TString(periodForPrw).Contains("None") != 1)
  {
    submitDir << "prwTo"<< periodForPrw << "-";
  } 

  submitDir << datime.str() << "_" << label;

  std::cout << "Submit Dir :: " << submitDir.str() << std::endl;

  // Do submission
  driver.submitOnly (job, submitDir.str());
  std::cout << sep;
  std::cout << "See output in: " << submitDir.str() << std::endl;
}
