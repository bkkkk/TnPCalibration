#ifndef SCALEFACTORMAKER_H_
#define SCALEFACTORMAKER_H_ 1

class ScaleFactorMaker
{

public:
  /// Ctor
  ScaleFactorMaker();

public:
  /// Dtor
  ~ScaleFactorMaker();

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
  /// Name of object
  std::string name;

  /// Pointer to files
  TFile*      mcFile;
  TFile*      dataFile;
};

#endif