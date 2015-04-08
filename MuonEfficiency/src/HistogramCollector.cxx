#include "MuonEfficiency/HistogramCollector.h"
#include "TnPSelector/CutflowCollector.h"
#include "D3PDReaderAdapter/IWorker.h"
#include "JacobUtils/LoggingUtility.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>

HC::HistogramCollector::HistogramCollector(const std::string& name,
                                           IWorker* worker)
    : name{std::move(name)}, wk{worker} {
  if (!wk) {
    LOG_WARNING() << "Running in testing mode, the histograms won't be "
                     "registered with worker node";
  }
}

int HC::HistogramCollector::CreateHistogramGroup(
    const std::string& baseName,
    const std::vector<std::string>& nameSuffixes,
    const std::string& baseTitle,
    const std::vector<std::string>& titleSuffixes,
    const unsigned int nbins,
    const float min,
    const float max) {
  if (nameSuffixes.size() != titleSuffixes.size()) {
    LOG_WARNING() << "You have more/less titles then names in group for: "
                  << baseName;
    LOG_WARNING() << "Histogram Group not created";
    return (0);
  }

  for (size_t histoIdx = 0; histoIdx != nameSuffixes.size(); histoIdx++) {
    auto name = baseName + "_" + nameSuffixes[histoIdx];
    auto title = baseTitle + "_" + titleSuffixes[histoIdx];

    CreateHistogram(name, title, nbins, min, max);
  }

  return (1);
}

int HC::HistogramCollector::CreateHistogramGroup(
    const std::string& baseName,
    const std::vector<std::string>& nameSuffixes,
    const std::string& baseTitle,
    const std::vector<std::string>& titleSuffixes,
    const unsigned int nbinsx,
    const float minx,
    const float maxx,
    const unsigned int nbinsy,
    const float miny,
    const float maxy) {
  if (nameSuffixes.size() != titleSuffixes.size()) {
    LOG_WARNING() << "You have more/less titles then names in group for: "
                  << baseName;
    LOG_WARNING() << "Histogram Group not created";
    return (0);
  }

  for (size_t histoIdx = 0; histoIdx != nameSuffixes.size(); histoIdx++) {
    auto name = baseName + "_" + nameSuffixes[histoIdx];
    auto title = baseTitle + "_" + titleSuffixes[histoIdx];

    CreateHistogram(name, title, nbinsx, minx, maxx, nbinsy, miny, maxy);
  }

  return (1);
}

int HC::HistogramCollector::CreateHistogramGroup(
    const std::string& baseName,
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
    const float maxz) {
  if (nameSuffixes.size() != titleSuffixes.size()) {
    LOG_WARNING() << "You have more/less titles then names in group for: "
                  << baseName;
    LOG_WARNING() << "Histogram Group not created";
    return (0);
  }

  for (size_t histoIdx = 0; histoIdx != nameSuffixes.size(); histoIdx++) {
    auto name = baseName + "_" + nameSuffixes[histoIdx];
    auto title = baseTitle + "_" + titleSuffixes[histoIdx];

    CreateHistogram(name,
                    title,
                    nbinsx,
                    minx,
                    maxx,
                    nbinsy,
                    miny,
                    maxy,
                    nbinsz,
                    minz,
                    maxz);
  }

  return (1);
}

int HC::HistogramCollector::CreateHistogram(const std::string& name,
                                            const std::string& title,
                                            CutflowCollector* acceptObject) {
  if (!acceptObject) {
    LOG_WARNING() << "Accept object is NULL, cannot create cutflow histogram";
    return (0);
  }

  auto bins = acceptObject->getNCuts();
  auto min = -0.5;
  auto max = bins - 0.5;

  auto status = CreateHistogram(name, title, bins, min, max);

  for (auto bin = 1ul; bin != bins + 1; bin++) {
    mapHistos[name]->GetXaxis()->SetBinLabel(bin,
                                             acceptObject->getCutName(bin - 1));
  }

  return (status);
}

int HC::HistogramCollector::CreateHistogram(const std::string& name,
                                            const std::string& title,
                                            const unsigned int nbinsx,
                                            const float minx,
                                            const float maxx) {
  histoNames.push_back(name);
  mapHistos[name] = new TH1F(name.c_str(), title.c_str(), nbinsx, minx, maxx);

  LOG_DEBUG3() << "Adding histogram " << name << " to collection";

  if (wk)
    wk->addOutput(mapHistos[name]);

  return (1);
}

int HC::HistogramCollector::CreateHistogram(const std::string& name,
                                            const std::string& title,
                                            const unsigned int nbinsx,
                                            const float minx,
                                            const float maxx,
                                            const unsigned int nbinsy,
                                            const float miny,
                                            const float maxy) {
  histoNames2D.push_back(name);
  mapHistos2D[name] = new TH2F(
      name.c_str(), title.c_str(), nbinsx, minx, maxx, nbinsy, miny, maxy);

  LOG_DEBUG3() << "Adding histogram " << name << " to collection";

  if (wk)
    wk->addOutput(mapHistos2D[name]);

  return (1);
}

int HC::HistogramCollector::CreateHistogram(const std::string& name,
                                            const std::string& title,
                                            const unsigned int nbinsx,
                                            const float minx,
                                            const float maxx,
                                            const unsigned int nbinsy,
                                            const float miny,
                                            const float maxy,
                                            const unsigned int nbinsz,
                                            const float minz,
                                            const float maxz) {
  histoNames3D.push_back(name);
  mapHistos3D[name] = new TH3F(name.c_str(),
                               title.c_str(),
                               nbinsx,
                               minx,
                               maxx,
                               nbinsy,
                               miny,
                               maxy,
                               nbinsz,
                               minz,
                               maxz);

  LOG_DEBUG3() << "Adding histogram " << name << " to collection";

  if (wk)
    wk->addOutput(mapHistos3D[name]);
  return (1);
}

int HC::HistogramCollector::FillHistogram(const std::string& name,
                                          const float& value,
                                          const float& weight) {
  if (mapHistos.find(name) != mapHistos.end()) {
    mapHistos[name]->Fill(value, weight);
    return (1);
  } else {
    WarningNotFound(name);
    return (0);
  }
}

int HC::HistogramCollector::FillHistogram(const std::string& name,
                                          const float& valueX,
                                          const float& valueY,
                                          const float& weight) {
  if (mapHistos2D.find(name) != mapHistos2D.end()) {
    mapHistos2D[name]->Fill(valueX, valueY, weight);
  } else {
    WarningNotFound(name);
  }

  return (1);
}

int HC::HistogramCollector::FillHistogram(const std::string& name,
                                          const float& valueX,
                                          const float& valueY,
                                          const float& valueZ,
                                          const float& weight) {
  if (mapHistos3D.find(name) != mapHistos3D.end()) {
    mapHistos3D[name]->Fill(valueX, valueY, valueZ, weight);
  } else {
    WarningNotFound(name);
  }

  return (1);
}

int HC::HistogramCollector::FillHistogram(const std::string& name,
                                          CutflowCollector* accept,
                                          const float weight) {
  if (!accept) {
    LOG_WARNING() << "TAccept object is empty";
  }

  if (mapHistos.find(name) != mapHistos.end()) {
    for (size_t cutIdx = 0; cutIdx != accept->getNCuts(); cutIdx++) {
      if (accept->getCutResult(cutIdx) != 0) {
        mapHistos[name]->Fill(accept->getCutName(cutIdx), weight);
      }
    }
  } else {
    WarningNotFound(name);
  }
  return (1);
}

TH1F* HC::HistogramCollector::GetHistogram1D(const std::string& name) {
  if (mapHistos.find(name) != mapHistos.end())
    return (mapHistos[name]);
  else {
    WarningNotFound(name);
    return (nullptr);
  }
}

TH2F* HC::HistogramCollector::GetHistogram2D(const std::string& name) {
  if (mapHistos2D.find(name) != mapHistos2D.end()) {
    return (mapHistos2D[name]);
  } else {
    WarningNotFound(name);
    return (nullptr);
  }
}

TH3F* HC::HistogramCollector::GetHistogram3D(const std::string& name) {
  if (mapHistos3D.find(name) != mapHistos3D.end())
    return (mapHistos3D[name]);
  else {
    WarningNotFound(name);
    return (nullptr);
  }
}

void HC::HistogramCollector::WarningNotFound(const std::string& name) {
  LOG_WARNING() << "Couldn't find histogram: " << name << " in collection";
}
