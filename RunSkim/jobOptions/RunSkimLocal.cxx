void RunSkimLocal ( const std::string samplePath,
                    const std::string& submitDir )
{  
  /// Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  /// Output name
  std::string outputName = "output";

  /// Create a new SampleHandler to grab all samples
  std::cout << "Loading Event Trees" << std::endl;
  SH::SampleHandler sh;
  SH::scanDir (sh, samplePath);
  sh.setMetaString ("nc_tree", "physics");
  std::cout << "Loading complete" << std::endl;

  sh.print ();

  /// Create a new job
  EL::Job job;
  job.sampleHandler (sh);

  /// Create and Output Stream and add to job
  EL::OutputStream output (outputName);
  job.outputAdd (output);

  /// Create ntuple service
  /// and set it up
  EL::NTupleSvc *ntuple = new EL::NTupleSvc (outputName);

  std::string controlDir = getenv("CONTROLDIR");

  std::string branchFile = controlDir + "/branches.txt";
  std::string triggerFile = controlDir + "/triggers.txt";


  /// Grab list of branches from file
  std::vector<std::string> branchList; 
  int status = RT::GetListFromFile(branchFile.c_str(), branchList);
  std::vector<std::string>::iterator branch = branchList.begin();
  std::vector<std::string>::iterator lastBranch = branchList.end();

  for(;branch!=lastBranch;++branch)
  {
    ntuple->copyBranch((*branch).c_str());
  };

  /// Add ntuple algorithm to job
  job.algsAdd(ntuple);

  /// Add MiniNtupleMaker algorithm to job
  MIN::MiniNtupleMaker *miniNtupleMaker = new MIN::MiniNtupleMaker;
  miniNtupleMaker->outputName = outputName;

  // Configure trigger list
  std::vector<std::string> triggerList;
  status = RT::GetListFromFile(triggerFile, triggerList);
  
  /// Configure GRL tool
  Root::TGoodRunsListReader* grlR = new Root::TGoodRunsListReader ( );
  grlR->SetXMLFile ("/scratch0/jblanco/CalibrationWork/RootCore/data/GoodRunsLists/data12_8TeV.periodAllYear_DetStatus-v54-pro13-04_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml");
  grlR->Interpret ();

  // Configure selectors
  TJPsiTagSelector* tagSelector = new TJPsiTagSelector();
  tagSelector->etaCut = 2.5;
  tagSelector->combinedMuonCut = 1;
  tagSelector->ptCut = 4000.;
  tagSelector->d0Cut = 0.3;
  tagSelector->z0Cut = 1.5;
  tagSelector->d0SigCut = 3;
  tagSelector->z0SigCut = 3;

  TMCPSelector* mcpSelector = new TMCPSelector();

  TTriggerMatching* triggerMatching = new TTriggerMatching();
  triggerMatching->dRCut = 0.15;

  /// Set analysis selectors, trigger list, GRL selector.
  miniNtupleMaker->triggerList = triggerList;
  miniNtupleMaker->my_grl = grlR->GetMergedGoodRunsList( );
  miniNtupleMaker->tagSelector = tagSelector;
  miniNtupleMaker->mcpSelector = mcpSelector;
  miniNtupleMaker->eventDebug = 10;
  miniNtupleMaker->triggerMatching = triggerMatching;

  job.options()->setDouble (EL::Job::optMaxEvents, 1000);


  job.algsAdd(miniNtupleMaker);
  /// Create a new driver
  EL::DirectDriver driver;

  /// process the job using the driver
  driver.submit (job, submitDir);
}
