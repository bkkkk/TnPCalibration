#ifndef SKIMMING_SKIMLISTEXCEPTIONS_H_
#define SKIMMING_SKIMLISTEXCEPTIONS_H_ 1

#include <stdexcept>
#include <iostream>

namespace Skimming {

struct collection_not_found : public std::runtime_error {
  explicit collection_not_found(const std::string& collection) throw()
   : std::runtime_error (collection),
     collectionname(collection) { }

  ~collection_not_found() throw() { }

  const char* what() const throw() {
    return "Collection not found\n";
  }

  std::string collectionname;
};

struct sample_not_found : public std::runtime_error {
  explicit sample_not_found(const std::string& sample) throw()
  : std::runtime_error(sample),
    samplename(sample) { }

  ~sample_not_found() throw() { }
  const char* what() const throw() { return "Sample not found!\n"; }

  std::string samplename;
};

struct cannot_create_file : public std::runtime_error {
  explicit cannot_create_file(const std::string& file) throw()
  : std::runtime_error(file),
    filename(file) { }

  ~cannot_create_file() throw() { }

  const char* what() const throw() { return "File not found!\n"; }

  std::string filename;
};

}

#endif
