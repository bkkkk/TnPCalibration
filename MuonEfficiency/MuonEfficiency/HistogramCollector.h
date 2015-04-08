#ifndef HISTOGRAM_COLLECTOR_H_
#define HISTOGRAM_COLLECTOR_H_ 1

#include <map>
#include <vector>
#include <string>

class IWorker;
class TH1F;
class TH2F;
class TH3F;
class CutflowCollector;

namespace HC {

class HistogramCollector {
 public:
  HistogramCollector(const std::string& name, IWorker* worker);
  ~HistogramCollector();

  int CreateHistogramGroup(const std::string& baseName,
                           const std::vector<std::string>& nameSuffixes,
                           const std::string& baseTitle,
                           const std::vector<std::string>& titleSuffixes,
                           const unsigned int nbins,
                           const float min,
                           const float max);

  int CreateHistogramGroup(const std::string& baseName,
                           const std::vector<std::string>& nameSuffixes,
                           const std::string& baseTitle,
                           const std::vector<std::string>& titleSuffixes,
                           const unsigned int nbinsx,
                           const float minx,
                           const float maxx,
                           const unsigned int nbinsy,
                           const float miny,
                           const float maxy);

  int CreateHistogramGroup(const std::string& baseName,
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
                           const float maxz);

  int CreateHistogram(const std::string& name,
                      const std::string& title,
                      CutflowCollector* acceptObject);

  int CreateHistogram(const std::string& name,
                      const std::string& title,
                      const unsigned int nbins,
                      const float min,
                      const float max);

  int CreateHistogram(const std::string& name,
                      const std::string& title,
                      const unsigned int nbinsx,
                      const float minx,
                      const float maxx,
                      const unsigned int nbinsy,
                      const float miny,
                      const float maxy);

  int CreateHistogram(const std::string& name,
                      const std::string& title,
                      const unsigned int nbinsx,
                      const float minx,
                      const float maxx,
                      const unsigned int nbinsy,
                      const float miny,
                      const float maxy,
                      const unsigned int nbinsz,
                      const float minz,
                      const float maxz);

  int FillHistogram(const std::string& name,
                    const float& value,
                    const float& weight);

  int FillHistogram(const std::string& name,
                    const float& valueX,
                    const float& valueY,
                    const float& weight);

  int FillHistogram(const std::string& name,
                    const float& valueX,
                    const float& valueY,
                    const float& valueZ,
                    const float& weight);

  int FillHistogram(const std::string& name,
                    CutflowCollector* accept,
                    const float weight);

 public:
  TH1F* GetHistogram1D(const std::string& name);
  TH2F* GetHistogram2D(const std::string& name);
  TH3F* GetHistogram3D(const std::string& name);

 private:
  inline void WarningNotFound(const std::string& name);

 public:
  std::string name;

 private:
  IWorker* wk;

 public:
  std::vector<std::string> histoNames;
  std::vector<std::string> histoNames2D;
  std::vector<std::string> histoNames3D;

 private:
  std::map<std::string, TH1F*> mapHistos;
  std::map<std::string, TH2F*> mapHistos2D;
  std::map<std::string, TH3F*> mapHistos3D;
};
}

#endif