// @file
// Holds enums used by the truth tools packages

#ifndef TRUTH_TOOLS_ENUMS_H_
#define TRUTH_TOOLS_ENUMS_H_ 1

// Truth Tools Namespace
namespace TT
{
  // Enum to hold reference to sibling type
  typedef enum
  {
    PARENT = 0,
    CURRENT = 1,
    CHILD = 2
  } siblingType;

  // Enum to hold PDG ID numbers
  typedef enum
  {
    // Quarks
    DQUARK = 1, // Down Quark
    UQUARK = 2, // Up Quark
    SQUARK = 3, // Strange Quark
    CQUARK = 4, // Charm Quark
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

}; // End Namespace TT

#endif
// END TRUTH_TOOLS_ENUMS_H_
