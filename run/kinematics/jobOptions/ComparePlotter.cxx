void ComparePlotter(const std::string& mcPath, const std::string& outputDir = "./") {
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  using NameLabel = std::pair<std::string, std::string>;

  std::vector<NameLabel> names_and_labels = {
    {"h_tag_z0_PV", "Tag z0 PV"},
    {"h_probe_z0_PV", "Probe z0 PV"}
  };

  TFile* file = new TFile(mcPath.c_str());

  for(const auto& name_label : names_and_labels) {
    auto weighted_name = name_label.first + "_wgt";

    auto histoOne = dynamic_cast<TH1F*>(file->Get(name_label.first.c_str()));
    auto histoTwo = dynamic_cast<TH1F*>(file->Get(weighted_name.c_str()));

    GT::ScaleFactor testSF(names[i] + "comparison", histoOne, histoTwo);
    testSF.SetXaxisTitle("z0 [mm]");
    testSF.SetYaxisTitle("Muon");
    testSF.SetSFaxisTitle("#Delta");
    testSF.doLog = 1;
    testSF.colorTwo = kRed; testSF.markerStyleTwo = 25; testSF.histo1Title = labels[i] + " Unweighted";
    testSF.colorOne = kBlue; testSF.markerStyleOne = 26; testSF.histo2Title = labels[i] + " Weighted";;
    testSF.Draw();
    testSF.SaveAs("./" + names[i] + ".png", "png");
  }
}
