void ComparePlotter( const std::string& mcPath,
                 const std::string& outputDir="./")
{
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  std::string names[] = { "h_tag_z0_PV", "h_probe_z0_PV"};
  std::string label[] = { "Tag z0 PV", "Probe z0 PV"};

  TFile* file = new TFile(mcPath.c_str());
  
  for(int i=0; i != 2; i++)
  {
    std::string unwgtName = names[i];
    std::string wgtName = names[i] + "_wgt";

    TH1F* histoOne = dynamic_cast<TH1F*>(file->Get( unwgtName.c_str() ));
    TH1F* histoTwo = dynamic_cast<TH1F*>(file->Get( wgtName.c_str() ));

    GT::ScaleFactor testSF(names[i] + "comparison", histoOne, histoTwo);
    testSF.SetXaxisTitle("z0 [mm]");
    testSF.SetYaxisTitle("Muon");
    testSF.SetSFaxisTitle("#Delta");
    testSF.doLog = 1;
    testSF.colorTwo = kRed; testSF.markerStyleTwo = 25; testSF.histo1Title = label[i] + " Unweighted";
    testSF.colorOne = kBlue; testSF.markerStyleOne = 26; testSF.histo2Title = label[i] + " Weighted";;
    testSF.Draw();
    testSF.SaveAs("./" + names[i] + ".png", "png");
  }
};
