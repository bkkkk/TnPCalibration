#pragma once

#include <iostream>
#include <exception>

template<typename T>
class MatchResult {
  using MatchObject = T;

public:
  friend std::ostream& operator<<(std::ostream& stream, MatchResult<MatchObject> const& f);

public:
  MatchResult(bool matchFound, double matchDistance, MatchObject matchedTo)
   : m_MatchFound{matchFound}
   , m_MatchDistance{matchDistance}
   , m_MatchedTo{matchedTo} {
  }

  MatchResult()
   : m_MatchFound{false}
   , m_MatchDistance{0.0}
   , m_MatchedTo{} {
  }

  bool operator()() {
    return (m_MatchFound);
  }

  double getDistance() {
    if(!m_MatchFound) {
      throw(std::runtime_error("Matching has failed, there is no valid distance."));
    }

    return (m_MatchDistance);
  }

  MatchObject getMatched() {
    return (m_MatchedTo);
  }

  void setFound(double distance, MatchObject matchedTo) {
    m_MatchFound = true;
    m_MatchDistance = distance;
    m_MatchedTo = matchedTo;
  }

private:
  bool m_MatchFound;
  double m_MatchDistance;
  MatchObject m_MatchedTo;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, MatchResult<T> const& f) {
  if (f.m_MatchFound) {
    return stream << "Match not found";
  } else {
    return stream << "Match found with distance = " << f.m_MatchDistance;
  }
}
