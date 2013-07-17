#ifndef SUMMARYPLOTMAKER_H_
#define SUMMARYPLOTMAKER_H_ 1

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TFile.h"
#include "MuonEfficiency/TnPSlices.h"

class SummaryPlotMaker
{

public:
  enum SampleType
  {
    kMC = 100,
    kDATA = 101
  };

public:
  //
  SummaryPlotMaker(const std::string& fileLabel);

public:
  ///
  virtual ~SummaryPlotMaker(void);

public:
  ///
  int FillEfficiencyHistograms( const SampleType type,
                                const std::string& varName,
                                const std::vector<std::pair<float, float> >& slices,
                                TH1F& recoHisto,
                                TH1F& smtHisto,
                                const std::string& prefix = "" );

  /// 
  int FillEfficiencyHistograms( TFile* file,
                                const std::string& typeName,
                                const std::string& varName,
                                const std::vector<std::pair<float, float> >& slices,
                                TH1F& recoHisto,
                                TH1F& smtHisto,
                                const std::string& prefix = "" );

public:
  ///
  int SaveScaleFactorHistograms( const std::string& varName );
  
public:
  /// Save Scale Factor histograms for binned in global variable
  /// 
  int SaveScaleFactorHistograms( const std::string& varName, 
                                 const std::string& global );

public:
  /// Build SF histos from two histograms
  int MakeSFHistograms( const TH1F* mc, const TH1F* data, TH1F& outputHisto );

public:
  ///
  int AddMCSample( const std::string& path );
  int AddMCSample( TFile* file );

public:
  ///
  int AddDataSample( const std::string& path );
  int AddDataSample( TFile* file );

private:
  ///
  int AddSample( const SampleType mode, const std::string& filePath );
  int AddSample( const SampleType mode, TFile* file );

private:
  ///
  std::string GetRegionName(const size_t region);

private:
  /// 
  float GetTotalError(const float eff, const float statErr, const float systErr);
  
  /// Pointer to files
  TFile*      mcFile;
  TFile*      dataFile;

  /// For rdbuffer outputs
  std::streambuf* psbuf;
  std::streambuf* backup;
  std::ofstream fitOutput;

  /// Pointer to output file
  TFile*      outputFile;

  public:
  /// Slices object
  TnPSlices*   tnpSlices;

  ClassDef(SummaryPlotMaker, 1)
};

#endif
