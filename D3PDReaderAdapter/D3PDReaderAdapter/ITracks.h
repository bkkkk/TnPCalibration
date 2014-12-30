#ifndef D3PDREADERADAPTER_ITRACKS_HPP
#define D3PDREADERADAPTER_ITRACKS_HPP 1

#include <D3PDReaderAdapter/ITrack.h>
#include <cstddef>

class ITracks
{
public:
  ITracks();
  virtual ~ITracks();
  
  virtual std::size_t n() = 0;
  virtual const std::size_t n() const = 0;

  virtual ITrack& operator[](std::size_t idx) = 0;
  virtual const ITrack& operator[](std::size_t idx) const = 0;
};

#endif