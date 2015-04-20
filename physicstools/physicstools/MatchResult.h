#pragma once

class MatchResult {
public:
  friend std::ostream& operator<<(std::ostream& stream, MatchResult const& f);

public:
  MatchResult(bool matchFound, double matchDistance) 
   : m_MatchFound{matchFound}
   , m_MatchDistance{matchDistance} { 
    (void)m_MatchFound;
    (void)m_MatchDistance;
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

private:
  bool m_MatchFound;
  double m_MatchDistance;
};

std::ostream& operator<<(std::ostream& stream, MatchResult const& f) {
  if (f.m_MatchFound) {
    return stream << "Match not found";
  } else {
    return stream << "Match found with distance = " << f.m_MatchDistance;
  }
}
