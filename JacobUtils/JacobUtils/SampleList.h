#ifndef JACOBUTILS_SAMPLELIST_H_
#define JACOBUTILS_SAMPLELIST_H_ 1
#include <map>
#include <string>

#include "TNamed.h"

class TFile;

namespace ST
{
  class SampleList
  {
  public:
    // Create a new interface object to XML file
    // @par path Path to XML file repo
    SampleList(const std::string& path);

    // Create a new interface object to XML file
    SampleList(TFile* path);
  
    // Returns the path of sample name
    std::string GetPath(const std::string& name);

    // Add sample with path
    void AddSample(const std::string& sample, const std::string& path);
    
    // Remove Sample from list
    void RemoveSample(const std::string& sample);
    
    void Write(void);

    // Prints all the samples in the repo
    //
    void Print(void);

    // Delete stuff
    ~SampleList();

  private:
    bool IsPresent(const std::string& name)
    {
      return ((*sampleMap).find(name) == (*sampleMap).end());
    }

  private:
    TFile* dataset;
    typedef std::map<std::string, std::string> SampleMap;
    SampleMap* sampleMap;

    ClassDef(ST::SampleList, 1)
  };
}

#endif