#ifndef HISTOGRAM_COLLECTOR_H_
#define HISTOGRAM_COLLECTOR_H_ 1

#include <map>
#include <vector>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include <EventLoop/Worker.h>

namespace Root{
  class TAccept;
}

namespace HC
{

  class HistogramCollector
  {
  public:
    HistogramCollector( const std::string& val_name, EL::Worker* worker );
  
  public:
    ~HistogramCollector();

  public:
    std::string name;

  private:
    EL::Worker* wk;  


  public:
    std::vector<std::string> histoNames;
    std::vector<std::string> histoNames2D;
    std::vector<std::string> histoNames3D;

  public:
    int CreateHistogramGroup( const std::string& baseName,
                              const std::vector<std::string>& nameSuffixes,
                              const std::string& baseTitle,
                              const std::vector<std::string>& titleSuffixes,
                              const unsigned int nbins,
                              const float min,
                              const float max );

  public:
    // 2D creator
    int CreateHistogramGroup( const std::string& baseName,
                              const std::vector<std::string>& nameSuffixes,
                              const std::string& baseTitle,
                              const std::vector<std::string>& titleSuffixes,
                              const unsigned int nbinsx,
                              const float minx,
                              const float maxx,
                              const unsigned int nbinsy,
                              const float miny,
                              const float maxy );

  public:
    // 3D creator
    int CreateHistogramGroup( const std::string& baseName,
                              const std::vector<std::string>& nameSuffixes,
                              const std::string& baseTitle,
                              const std::vector<std::string>& titleSuffixes,
                              const unsigned int nbinsx,
                              const float minx,
                              const float maxx,
                              const unsigned int nbinsy,
                              const float miny,
                              const float maxy,
                              const unsigned int nbinsz,
                              const float minz,
                              const float maxz );

  public:
    // 1D Cutflow Histogram
    int CreateHistogram( const std::string& name,
                         const std::string& title,
                         const Root::TAccept* acceptObject );

  public:
    // 1D creator
    int CreateHistogram( const std::string& name,
                         const std::string& title,
                         const unsigned int nbins,
                         const float min,
                         const float max );

  public:
    // 2D creator
    int CreateHistogram( const std::string& name,
                         const std::string& title,
                         const unsigned int nbinsx,
                         const float minx,
                         const float maxx,
                         const unsigned int nbinsy,
                         const float miny,
                         const float maxy );

  public:
    // 3D creator
    int CreateHistogram( const std::string& name,
                         const std::string& title,
                         const unsigned int nbinsx,
                         const float minx,
                         const float maxx,
                         const unsigned int nbinsy,
                         const float miny,
                         const float maxy,
                         const unsigned int nbinsz,
                         const float minz,
                         const float maxz );

  public:
    /// 1D Fillers
    int FillHistogram ( const std::string& name, const float& value,
                        const float& weight );

    /// 2D Filler
    int FillHistogram ( const std::string& name, const float& valueX,
                        const float& valueY, const float& weight);

    /// 3D Filler
    int FillHistogram ( const std::string& name, const float& valueX,
                        const float& valueY, const float& valueZ,
                        const float& weight);

    /// Fill Cutflow
    int FillHistogram( const std::string& name,
                       const Root::TAccept* accept,
                       const float weight );

  public:
    // 1D Getter
    TH1F* GetHistogram1D( const std::string& name );
    TH2F* GetHistogram2D( const std::string& name );
    TH3F* GetHistogram3D( const std::string& name );

  private:
    const inline void WarningNotFound( const std::string& name );

  private:
    std::map<std::string, TH1F*> mapHistos;
    std::map<std::string, TH2F*> mapHistos2D;
    std::map<std::string, TH3F*> mapHistos3D;
  };

}

#endif