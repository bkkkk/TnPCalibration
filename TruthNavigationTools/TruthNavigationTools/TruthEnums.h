#ifndef TRUTH_TOOLS_ENUMS_H_
#define TRUTH_TOOLS_ENUMS_H_ 1

namespace TT {
  typedef enum {
    PARENT = 0,
    CURRENT = 1,
    CHILD = 2
  } siblingType;

  typedef enum {
    // Quarks
    DQUARK = 1,
    UQUARK = 2,
    SQUARK = 3,
    CQUARK = 4,
    BQUARK = 5,
    TQUARK = 6,
    
    // Leptons
    ELECTRON = 11,
    NUELECTRON = 12,
    MUON = 13,
    NUMUON = 14,
    TAU = 15,
    NUTAU = 16,

    // Bosons
    GLUON = 21,
    PHOTON = 22,
    ZBOSON = 23,
    WPLUSBOSON = 24,
  } particlePdgId;

};

#endif
