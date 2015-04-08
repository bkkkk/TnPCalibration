#ifndef WEIGHTING_H_
#define WEIGHTING_H_ 1

#include <string>
#include "D3PDReaderAdapter/IEvent.h"

class Weighting {
 protected:
  Weighting(std::string name, std::string title)
      : m_name{std::move(name)}, m_title{std::move(title)} {}
  virtual ~Weighting() = default;

 public:
  inline std::string GetName() { return m_name; }
  inline std::string GetTitle() { return m_title; }
  virtual double GetWeight(IEvent* event) = 0;

 protected:
  std::string m_name;
  std::string m_title;

#ifdef __CINT__
  ClassDef(Weighting, 1);
#endif
};

#endif