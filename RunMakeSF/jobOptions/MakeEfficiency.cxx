void MakeEfficiency (const std::string& inputDirData, const std::string& inputDirMC, const std::string& label)
{
  // Load the libraries for all packages
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  SummaryPlotMaker* plotMaker = new SummaryPlotMaker(label);

  TnPSlices* tnpSlices = new TnPSlices();

  std::string controlDir = getenv("CONTROLDIR");

  tnpSlices->AddSlices("pt", controlDir + "/pt.txt");
  tnpSlices->AddSlices("eta", controlDir + "/eta.txt");
  tnpSlices->AddSlices("phi", controlDir + "/phi.txt");
  tnpSlices->AddSlices("etcone20", controlDir + "/etcone20.txt");
  tnpSlices->AddSlices("etcone30", controlDir + "/etcone30.txt");
  tnpSlices->AddSlices("etcone40", controlDir + "/etcone40.txt");
  tnpSlices->AddSlices("ptcone20", controlDir + "/ptcone20.txt");
  tnpSlices->AddSlices("ptcone30", controlDir + "/ptcone30.txt");
  tnpSlices->AddSlices("ptcone40", controlDir + "/ptcone40.txt");
  tnpSlices->AddSlices("nucone20", controlDir + "/nucone20.txt");
  tnpSlices->AddSlices("nucone30", controlDir + "/nucone30.txt");
  tnpSlices->AddSlices("nucone40", controlDir + "/nucone40.txt");

  tnpSlices->Initialize();

  plotMaker->tnpSlices = tnpSlices;
  
  plotMaker->AddMCSample(inputDirMC);
  plotMaker->AddDataSample(inputDirData);

  plotMaker->SaveScaleFactorHistograms("pt", "eta");
  plotMaker->SaveScaleFactorHistograms("eta");
  plotMaker->SaveScaleFactorHistograms("pt");
  plotMaker->SaveScaleFactorHistograms("phi");
  plotMaker->SaveScaleFactorHistograms("etcone20");
  plotMaker->SaveScaleFactorHistograms("etcone30");
  plotMaker->SaveScaleFactorHistograms("etcone40");
  plotMaker->SaveScaleFactorHistograms("ptcone20");
  plotMaker->SaveScaleFactorHistograms("ptcone30");
  plotMaker->SaveScaleFactorHistograms("ptcone40");
  plotMaker->SaveScaleFactorHistograms("nucone20");
  plotMaker->SaveScaleFactorHistograms("nucone30");
  plotMaker->SaveScaleFactorHistograms("nucone40");
};
