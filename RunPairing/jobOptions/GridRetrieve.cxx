void GridRetrieve (const std::string& submitDir)
{  
  /// Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  /// process the job using the driver
  EL::Driver::wait (submitDir);
}
