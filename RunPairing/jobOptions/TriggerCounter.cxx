#include <TFile.h>
#include <TTree.h>

#include <exception>
#include <iostream>
#include <string>

int CountOnlyThis(const std::string& trigger)
{

}

void TriggerCounter(const std::string& filePath)
{
  TFile* file = TFile::Open(filePath.data(), "OPEN");

  if(file->IsZombie() == 1)
  {
    std::cerr << "File not found" << std::endl;
    return;
  }

  TTree* tree;
  try
  {
    tree = dynamic_cast<TTree*> (file->Get("physics"));
  } catch (const std::exception& e) {
    std::cout << "Couldn't find a tree with the name physics" << std::endl;
    return;
  }

  // This is dumb
  std::string triggers[] = { "EF_mu10i_g10_medium_TauMass", 
                             "EF_mu10i_loose_g12Tvh_medium", 
                             "EF_mu10i_loose_g12Tvh_medium_TauMass", 
                             "EF_mu15", 
                             "EF_mu18_2g10_loose", 
                             "EF_mu18_2g10_medium", 
                             "EF_mu18_medium", 
                             "EF_mu18_tight_e7_medium1", 
                             "EF_mu20i_tight_g5_loose_TauMass", 
                             "EF_mu20i_tight_g5_medium_TauMass", 
                             "EF_mu20it_tight", 
                             "EF_mu22_IDTrkNoCut_tight", 
                             "EF_mu24_g20vh_loose", 
                             "EF_mu24_g20vh_medium", 
                             "EF_mu24_j65_a4tchad", 
                             "EF_mu24_j65_a4tchad_EFxe40_tclcw", 
                             "EF_mu24_j65_a4tchad_EFxe40wMu_tclcw", 
                             "EF_mu24_j65_a4tchad_EFxe60_tclcw", 
                             "EF_mu24_j65_a4tchad_EFxe60wMu_tclcw", 
                             "EF_mu24_medium", 
                             "EF_mu24_muCombTag_NoEF_tight", 
                             "EF_mu24_tight", 
                             "EF_mu24_tight_3j35_a4tchad", 
                             "EF_mu24_tight_3j45_a4tchad", 
                             "EF_mu24_tight_4j35_a4tchad", 
                             "EF_mu24_tight_4j45_a4tchad", 
                             "EF_mu24_tight_EFxe40", 
                             "EF_mu24_tight_L2StarB", 
                             "EF_mu24_tight_L2StarC", 
                             "EF_mu24_tight_MG", 
                             "EF_mu24_tight_MuonEF", 
                             "EF_mu24_tight_b35_mediumEF_j35_a4tchad", 
                             "EF_mu24i_tight", 
                             "EF_mu24i_tight_MG", 
                             "EF_mu24i_tight_MuonEF", 
                             "EF_mu24i_tight_muFast", 
                             "EF_mu36_tight", 
                             "EF_mu40_MSonly_barrel_tight", 
                             "EF_mu40_slow_tight", 
                             "EF_mu40_tight", 
                             "EF_mu4T", 
                             "EF_mu4T_L2StarB", 
                             "EF_mu4T_j65_a4tchad_xe60_tclcw_loose", 
                             "EF_mu4T_j65_a4tchad_xe70_tclcw_veryloose", 
                             "EF_mu50_MSonly_barrel_tight", 
                             "EF_mu6", 
                             "EF_mu60_slow_tight1", 
                             "EF_mu6T_2b55_medium_2j55_a4tchad_L1J20_matched", 
                             "EF_mu6_L2StarB", 
                             "EF_mu6_Trk_Jpsi_loose", 
                             "EF_mu6_Trk_Jpsi_loose_L2StarA", 
                             "EF_mu6_Trk_Jpsi_loose_L2StarB", 
                             "EF_mu8_4j45_a4tchad_L2FS" };

  for(int triggerIdx = 0; triggerIdx != 53; triggerIdx++)
  {
    std::string triggerName = triggers[triggerIdx];
    std::string selection = triggerName + " == 1";
    int count = tree->Draw("", selection.data());
    selection.append(" && EF_mu6_Trk_Jpsi_loose == 0 && EF_mu24i_tight == 0 && EF_mu36_tight == 0 && EF_mu20it_tight == 0 && EF_mu24_j65_a4tchad_EFxe40_tclcw == 0 && EF_mu20i_tight_g5_loose_TauMass == 0 && EF_mu24_j65_a4tchad_EFxe60wMu_tclcw == 0 && EF_mu24_tight == 0 && EF_mu24_tight_3j35_a4tchad == 0 &&  EF_mu24_j65_a4tchad_EFxe40wMu_tclcw == 0");
    int countWithNoEF = tree->Draw("", selection.data());

    std::cout << "|" << setw(50) << triggerName
              << "|" << setw(10) << count
              << "|" << setw(10) << countWithNoEF 
              << "|" << std::endl;
  };
  return;
}

