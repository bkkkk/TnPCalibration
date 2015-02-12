#ifndef D3PDREADERADAPTER_IMUONS_HPP
#define D3PDREADERADAPTER_IMUONS_HPP 1

#include <D3PDReaderAdapter/IMuon.h>
#include <cstddef>

class IMuons {
public:
  virtual ~IMuons();

  virtual std::size_t n() = 0;  
  virtual const std::size_t n() const = 0;

  virtual IMuon& operator[](std::size_t idx) = 0;
  virtual const IMuon& operator[](std::size_t idx) const = 0;
};

#endif

