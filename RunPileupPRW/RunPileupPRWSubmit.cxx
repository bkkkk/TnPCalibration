void RunPileupPRWSubmit (const std::string& inDS,
                         const std::string& submitDir)
{  
  /// Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  /// Output name
  std::string outputName = "output";

  /// Create a new SampleHandler to grab all samples
  SH::SampleHandler sh;
  SH::scanDQ2 (sh, inDS);
  sh.setMetaString ("nc_tree", "physics");
  sh.print ();

  /// Create a new job
  EL::Job job;
  job.sampleHandler (sh);

  /// Create and Output Stream and add to job
  EL::OutputStream output (outputName);
  job.outputAdd (output);

  /// Add MiniNtupleMaker algorithm to job
  PileupPRW *pileupPRW = new PileupPRW;
  pileupPRW->outputName = outputName;

  job.algsAdd(pileupPRW);
  
  /// Create a new driver
  EL::GridDriver driver;
  driver.athenaTag="17.6.0";
  
  /// process the job using the driver
  driver.submitOnly (job, submitDir);
}
