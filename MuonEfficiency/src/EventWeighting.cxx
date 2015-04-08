#include "MuonEfficiency/EventWeighting.h"
#include "MuonEfficiency/Weighting.h"
#include "JacobUtils/LoggingUtility.h"
#include "D3PDReaderAdapter/IEvent.h"

int EventWeighting::AddWeighting(Weighting* weighting) {
  m_weightings[weighting->GetName()] = weighting;
  return (1);
}

double EventWeighting::GetTotalWeighting(IEvent* event) {

  auto totalWgt = 1.0f;
  auto iter = m_weightings.begin();

  for (; iter != m_weightings.end(); iter++) {
    totalWgt *= (*iter).second->GetWeight(event);
  }

  return (totalWgt);
}

Weighting* EventWeighting::GetWeighting(const std::string& name) {
  if (m_weightings.find(name) != m_weightings.end()) {
    return (m_weightings[name]);
  } else {
    LOG_WARNING() << "Could not find weighting in map";
    return (NULL);
  }
}

#ifdef __CINT__
ClassImp(EventWeighting)
#endif
