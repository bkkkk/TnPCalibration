#ifndef SKIMMING_EXCEPTION_SAMPLENOTFOUND
#define SKIMMING_EXCEPTION_SAMPLENOTFOUND 1

class cannot_create_file : public std::runtime_error
{
public:
  // Ctor
  explicit cannot_create_file(const std::string& file) throw()
  : std::runtime_error(file),
    filename(file)
  {

  }

public:
  ~cannot_create_file() throw() 
  {
    
  }

public:
  // What
  const char* what() const throw()
  {
    return "File not found!\n";
  }

public:
  // File name
  std::string filename;
};

#endif