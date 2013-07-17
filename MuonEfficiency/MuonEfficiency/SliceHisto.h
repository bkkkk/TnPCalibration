#ifndef SLICEHISTO_H_
#define SLICEHISTO_H_ 1

#include <map>
#include <string>
#include "TH1F.h"

typedef enum
{
        PROBE = 1,
        MUONPROBE = 2,
        SMT = 3,
        DEFAULT = 1000
} HistoType;

class SliceHisto
{
public:
    SliceHisto(HistoType type, int bins, float min, float max);

public:
    ~SliceHisto();

public:
    int AddSliceVariable(const std::string variableName,
                         const float bottom,
                         const float top);

public:
    int Initialize(void);

public:
    int MakeName(void);

public:
    std::string LevelName();

public:
    TH1F* histo;

public:
    std::string sliceName;

public:
    std::string name;
    std::string title;

public:
    int nBins;
    float invMin;
    float invMax;

public:
    HistoType histType;

public:
    typedef std::map<std::string, std::pair<float, float> > Slices;
    Slices slices;
};

typedef std::vector<SliceHisto*> SliceCollection;

#endif
