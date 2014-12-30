#ifndef TNPSELECTOR_FAKEMUON_H_
#define TNPSELECTOR_FAKEMUON_H_ 1

#include <D3PDReaderAdapter/IMuon.h>

class FakeMuon : public IMuon
{
public:
  FakeMuon();
  ~FakeMuon();
};

#endif