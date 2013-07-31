#include "MuonEfficiency/SummaryPlotMaker.h"
#include "JacobUtils/LoggingUtility.h"
#include "JacobUtils/MathTools.h"
#include "MuonEfficiency/EfficiencyMaker.h"
#include "TnPFitter/FitEfficiency.h"
#include "THStack.h"

#include <math.h>

ClassImp(SummaryPlotMaker)

// =============================================================================

SummaryPlotMaker::SummaryPlotMaker(const std::string& fileLabel)
 : mcFile(NULL),
   dataFile(NULL),
   outputFile(NULL),
   tnpSlices(NULL)
{
  SET_LOG_LEVEL(kINFO);

  std::string prefix = "TnPFitResults";
  std::string fileName = prefix + "_" + fileLabel+ ".root";

  LOG_INFO() << "The output file is name: " << fileName;

  outputFile = new TFile(fileName.c_str(), "RECREATE");
};

// =============================================================================

SummaryPlotMaker ::
~SummaryPlotMaker(void)
{
};

// =============================================================================

int SummaryPlotMaker ::
SaveScaleFactorHistograms ( const std::string& varName,
                            const std::string& global )
{
  // StatusCode
  int StatusCode = 1;

  LOG_DEBUG1() << "Creating histograms";

  /// For Binning histograms
  std::vector< std::pair<float, float> > slices = tnpSlices->varMap[varName];
  std::vector<float> flatSlices = tnpSlices->flatSlices[varName];
  int nBins = slices.size();
  float* arraySlices = &flatSlices[0];

  // For Detector region cutting
  LOG_DEBUG1() << "Fetching regional slices: " << global;
  std::vector< std::pair<float, float> > regionSlices = tnpSlices->varMap[global];
  size_t nRegions = regionSlices.size();

  for (size_t region = 0; region != nRegions; region++)
  {
    LOG_DEBUG1() << "Looking at region: " << region;
    float lowerEdge = regionSlices[region].first;
    float upperEdge = regionSlices[region].second;

    LOG_DEBUG1() << "Lower edge: " << lowerEdge << " and upper edge: " << upperEdge;
    std::string regionLabel = Form("%s_%0.2f_%0.2f_", global.c_str(),
                                   lowerEdge, upperEdge);

    std::string regionName = this->GetRegionName( region );

    TH1F* recoEffData = new TH1F(Form("h_data_%s_%s_reco_eff", regionName.c_str(), varName.c_str()), "", nBins, arraySlices);
    TH1F* smtEffData  = new TH1F(Form("h_data_%s_%s_smt_eff", regionName.c_str(), varName.c_str()), "", nBins, arraySlices);
    TH1F* recoEffMc   = new TH1F(Form("h_mc_%s_%s_reco_eff", regionName.c_str(), varName.c_str()), "", nBins, arraySlices);
    TH1F* smtEffMc    = new TH1F(Form("h_mc_%s_%s_smt_eff", regionName.c_str(), varName.c_str()), "", nBins, arraySlices);

    outputFile->cd();
    StatusCode = FillEfficiencyHistograms( kDATA, varName, slices, *recoEffData, *smtEffData, regionLabel );
    StatusCode = FillEfficiencyHistograms( kMC, varName, slices, *recoEffMc, *smtEffMc, regionLabel );

    LOG_DEBUG() << "Initialized histos";

    /// Create stacks to hold MC vs Data efficiency distributions
    THStack* recoSFStack = new THStack ( Form( "h_%s_%s_reco_stack",
                                               varName.c_str(),
                                               regionName.c_str() ),
                                         Form("%s Reco Efficiency - %s ",
                                              varName.c_str(),
                                              regionName.c_str() ) );
    /// SMT
    THStack* smtSFStack = new THStack ( Form( "h_%s_%s_smt_stack",
                                              varName.c_str(),
                                              regionName.c_str() ),
                                        Form( "%s SMT Efficiency - %s",
                                              varName.c_str(),
                                              regionName.c_str() ) );


    /// Histograms to hold the Reconstruction SF
    TH1F* recoSF = new TH1F( Form( "h_%s_%s_reco_SF", varName.c_str(), regionName.c_str() ),
                             Form( "%s Reconstruction SF %s", varName.c_str(), regionName.c_str() ),
                             nBins, arraySlices );

    /// Histograms to hold the SMT SF
    TH1F* smtSF  = new TH1F( Form( "h_%s_%s_smt_SF", varName.c_str(), regionName.c_str() ),
                             Form( "%s SMT SF %s", varName.c_str(), regionName.c_str() ),
                             nBins, arraySlices );

    StatusCode = MakeSFHistograms(recoEffMc, recoEffData, *recoSF);
    StatusCode = MakeSFHistograms(smtEffMc, smtEffData, *smtSF);

    recoSFStack->Add(recoEffData);
    recoSFStack->Add(recoEffMc);
    recoSFStack->Write();

    smtSFStack->Add(smtEffData);
    smtSFStack->Add(smtEffMc);
    smtSFStack->Write();
    
    recoEffData->Write();
    recoEffMc->Write();
    smtEffData->Write();
    smtEffMc->Write();

    recoSF->Draw();
    recoSF->Write();

    smtSF->Draw();
    smtSF->Write();
  }; 
  return (StatusCode);
};

// =============================================================================


int SummaryPlotMaker ::
SaveScaleFactorHistograms( const std::string& varName )
{
  int status = 1;

  std::vector< std::pair<float, float> > slices = tnpSlices->varMap[varName];
  std::vector<float> flatSlices = tnpSlices->flatSlices[varName];
  int nBins = slices.size();
  float* arraySlices = &flatSlices[0];

  LOG_DEBUG() << "Making Scale Factor Histograms: " << varName;

  TH1F* recoEffData = new TH1F(Form("h_data_%s_reco_eff", varName.c_str()), "", nBins, arraySlices);
  TH1F* smtEffData  = new TH1F(Form("h_data_%s_smt_eff", varName.c_str()), "", nBins, arraySlices);
  TH1F* recoEffMc   = new TH1F(Form("h_mc_%s_reco_eff", varName.c_str()), "", nBins, arraySlices);
  TH1F* smtEffMc    = new TH1F(Form("h_mc_%s_smt_eff", varName.c_str()), "", nBins, arraySlices);

  LOG_DEBUG() << "Initialized histos";

  /// This needs to be here otherwise the fitting code will spit out warnings
  /// To do with output...might wanna fix this
  outputFile->cd();

  status = FillEfficiencyHistograms( kDATA, varName, slices, *recoEffData, *smtEffData );
  status = FillEfficiencyHistograms( kMC, varName, slices, *recoEffMc, *smtEffMc );

  LOG_DEBUG() << "Filled efficiencies";

  /// Create stacks to hold MC vs Data efficiency distributions
  THStack* recoSFStack = new THStack ( Form( "h_%s_reco_stack", varName.c_str() ),
                                       Form("Reco Efficiency %s", varName.c_str() ));
  /// SMT
  THStack* smtSFStack = new THStack ( Form( "h_%s_smt_stack", varName.c_str() ),
                                      Form("SMT Efficiency %s", varName.c_str() ));


  /// Histograms to hold the Reconstruction SF
  TH1F* recoSF = new TH1F( Form( "h_%s_reco_SF", varName.c_str() ),
                           Form( "Reconstruction SF %s",   varName.c_str() ),
                           nBins, arraySlices);

  /// Histograms to hold the SMT SF
  TH1F* smtSF  = new TH1F( Form( "h_%s_smt_SF", varName.c_str() ),
                           Form( "SMT SF %s",   varName.c_str() ),
                           nBins, arraySlices);

  
  status = MakeSFHistograms(recoEffMc, recoEffData, *recoSF);
  status = MakeSFHistograms(smtEffMc, smtEffData, *smtSF);

  outputFile->cd();

  if(outputFile==NULL)
  {
    LOG_ERROR() << "File got deleted somewhere";
    throw;
  }
  
  recoSFStack->Add(recoEffData);
  recoSFStack->Add(recoEffMc);

  status = recoEffData->Write();
  status = recoEffMc->Write();
  status = recoSFStack->Write();

  smtSFStack->Add(smtEffData);
  smtSFStack->Add(smtEffMc);

  outputFile->cd();
  status = smtEffData->Write();
  status = smtEffMc->Write();
  status = smtSFStack->Write();
  
  recoSF->Draw();
  status = recoSF->Write();
  
  smtSF->Draw();
  status = smtSF->Write();

  return (status);
};

// =============================================================================

int SummaryPlotMaker ::
FillEfficiencyHistograms(const SampleType type,
                         const std::string& varName,
                         const std::vector<std::pair<float, float> >& slices,
                         TH1F& recoHisto,
                         TH1F& smtHisto,
                         const std::string& prefix)
{
  switch(type)
  {
    case kMC:
      return(FillEfficiencyHistograms(mcFile, "MC", varName, slices, recoHisto, smtHisto, prefix));
    case kDATA:
      return(FillEfficiencyHistograms(dataFile, "Data", varName, slices, recoHisto, smtHisto, prefix));
    default:
      LOG_ERROR() << "Mode not correct";
      return (0);
  };
  return(0);
};

// =============================================================================

int SummaryPlotMaker ::
FillEfficiencyHistograms(TFile* file,
                         const std::string& typeName,
                         const std::string& varName,
                         const std::vector<std::pair<float, float> >& slices,
                         TH1F& recoHisto,
                         TH1F& smtHisto,
                         const std::string& prefix)
{
  LOG_INFO() << "Looping over slices in " << varName << " and " << prefix;

  for (size_t idx = 0; idx != slices.size(); idx++)
  {
    float lowEdge = slices[idx].first;
    float highEdge = slices[idx].second;

    std::string sliceName = Form("InvMass_%s_%0.2f_%0.2f_%s", varName.c_str(), lowEdge, highEdge, prefix.c_str());

    std::string probe = sliceName + "Probe";
    std::string muonprobe = sliceName + "MuonProbe";
    std::string smt = sliceName + "SMT";

    LOG_DEBUG1() << "Slice name: " << sliceName;

    TH1F* histoProbe = dynamic_cast<TH1F*>(file->Get(probe.c_str()));
    TH1F* histoMuonProbe = dynamic_cast<TH1F*>(file->Get(muonprobe.c_str()));
    TH1F* histoSMT = dynamic_cast<TH1F*>(file->Get(smt.c_str()));

    outputFile->cd();

    if (TString(varName).Contains("cone"))
    {
      LOG_INFO() << "This is an isolation variable" 
                 << ", Probe == MuonProbe distributions to keep things happy";
      histoProbe = histoMuonProbe;
    };

    std::string name = typeName + "_" + sliceName;

    FitEfficiency* fitEfficiency = new FitEfficiency(name, histoProbe, histoMuonProbe, histoSMT);
    fitEfficiency->Draw();

    outputFile->cd();

    float recoEff = fitEfficiency->GetRecoEfficiency();
    float recoTotalErr = fitEfficiency->GetRecoError();

    if((recoTotalErr / recoEff) > 0.2)
    {
      LOG_WARNING() << "Large Uncertainty : " << recoEff << "+-" << recoTotalErr << " from " << sliceName;
    }

    if(MathTools::isNan(recoEff))
    {
      LOG_WARNING() << "The reconstruction efficiency is NaN";
      continue;
    }

    LOG_INFO() << "Reconstruction efficiency: " << recoEff << "\u00b1" << recoTotalErr;

    recoHisto.Fill(lowEdge + 0.01, recoEff);
    recoHisto.SetBinError(idx + 1, recoTotalErr);
    
    /// SMT
    float matchChi2Eff = fitEfficiency->GetSMTEfficiency();
    float matchChi2TotalErr = fitEfficiency->GetSMTError();

    if(MathTools::isNan(matchChi2Eff))
    {
      LOG_WARNING() << "The SMT efficiency is NaN moving to next bin";
      continue;
    }
      
    if((matchChi2TotalErr / matchChi2Eff) > 0.2)
    {
      LOG_WARNING() << "Large Uncertainty : " << matchChi2Eff << "+-" << matchChi2TotalErr << " from " << sliceName;
    }

    smtHisto.Fill(lowEdge + 0.01, matchChi2Eff);
    smtHisto.SetBinError(idx + 1, matchChi2TotalErr);

    delete fitEfficiency;
  };



  LOG_INFO() << "Ending for " << varName << " and " << prefix;

  return (1);
};

// =============================================================================

int SummaryPlotMaker::AddMCSample(const std::string& path)
{
  return(AddSample(kMC, path));
};

// =============================================================================


int SummaryPlotMaker::AddMCSample(TFile* file)
{
  return (AddSample(kMC, file));
};

// =============================================================================

int SummaryPlotMaker::AddDataSample(const std::string& path)
{
  return(AddSample(kDATA, path));
};

// =============================================================================


int SummaryPlotMaker::AddDataSample(TFile* file)
{
  return (AddSample(kDATA, file));
};

// =============================================================================

int SummaryPlotMaker::AddSample(const SampleType mode,
                                const std::string& filePath)
{
  return( AddSample ( mode, new TFile( filePath.c_str() ) ) );
};

// =============================================================================


int SummaryPlotMaker::AddSample(const SampleType mode, TFile* file)
{
    // Check if file is opened properly
  if(file == NULL || file->IsZombie() == 1)
  {
    LOG_ERROR() << "Failed to open file: " << file->GetName();
    return (0);
  };

  switch(mode)
  {
    case kMC:
      mcFile = file;
      break;
    case kDATA:
      dataFile = file;
      break;
    default:
      LOG_ERROR() << "Mode not correct";
      return (0);
      break;
  };

  LOG_INFO() << "Sample loaded successfully";
  return (1);
};

// =============================================================================

float SummaryPlotMaker ::
GetTotalError(const float eff, const float statErr, const float systErr) 
{
    float statRel = statErr / eff;
    float systRel = systErr / eff;

    LOG_DEBUG2() << "Statistical error: " << statRel;
    LOG_DEBUG2() << "Systematics error: " << systRel;
    LOG_DEBUG2() << "Total Error: " << eff * sqrt(systRel * systRel + statRel * statRel);

    return(eff * sqrt(systRel * systRel + statRel * statRel));
};

// =============================================================================

int SummaryPlotMaker ::
MakeSFHistograms( const TH1F* mc, const TH1F* data, TH1F& outputHisto )
{
  /// Check if initialized
  if( !mc || !data)
  {
    LOG_ERROR() << "One of the input histograms has not been initialized correctly";
    return(0);
  };

  /// Check if histograms are compatible
  outputHisto.Divide(data, mc);

  /// If all is well
  return (1);
};


// =============================================================================

std::string SummaryPlotMaker :: 
GetRegionName ( const size_t region )
{
  static std::string temps[] = { "Forward C", "Endcap C", "Transition C", "Barrel C", "Crack C",
                                 "Crack A", "Barrel A", "Transition A", "Endcap A", "Forward A" };
  static std::vector<std::string> regionLabel(temps, temps + sizeof temps / sizeof temps[0] );

  if(region < 0 || regionLabel.size() > region) return(regionLabel.at(region));
  else return("Over");
};     


