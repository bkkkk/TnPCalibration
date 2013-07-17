#ifndef TNPSLICES_H_
#define TNPSLICES_H_ 1

#include <map>
#include <string>
#include <vector>
#include <TH1F.h>

typedef std::pair<float, float> Slice;
typedef std::vector<Slice> Slices;
typedef std::map<std::string, Slices> VariableMap;
typedef std::map<std::string, std::vector<float> > FlatSlices;

typedef std::vector<std::string> VariableName;

typedef enum
{
    kDONTREAD = -999999
} SliceEnum;

class TnPSlices
{
public:
    /// Create a collection of slices
    TnPSlices(const std::string& val_name="TnPSlices");

public:
    /// Dtor
    virtual ~TnPSlices(void);

public:
    /// Add a slice from a text file
    int AddSlices(std::string varName, std::string path);

public:
    /// Add a slice from a vector of floats
    int AddSlices(std::string varName, std::vector<float> slices);

public:
    /// Initialize
    int Initialize();

public:
    ///
    void PrintSlices(const std::string& var);

public:
    /// Get the appropriate slice label based on value for var
    /// Used when trying to find the correct histogram to fill
    /// for a probe with Variable var with Value = value
    /// (e.g. if pt = 6.2 GeV, slice is pt_6000_7000) 
    std::string GetSliceLabel(const std::string& var, const float value);
    
    /// Get Slice Label based on slice provided
    /// Can be used to construct the histogram name in the map based on
    /// user-defined slices
    #if 0
    std::string GetSliceLabel(const std::string& var, const Slice slicePair);
    #endif

public:
    ///
    void PrintSliceVector(const Slice& slice);

public:
    /// Get list of slice names
    VariableName GetListOfSlices(void);

public:
    /// Get the number of slices
    size_t GetNumberOfVariables(void);

public:
    /// Get the number of slices
    size_t GetNumberOfSlices(const std::string& var="pt");

public:
    ///
    std::string name;

public:
    /// Underlying storage object
    VariableMap varMap;
    VariableName varNames;
    FlatSlices flatSlices;

    ClassDef(TnPSlices,1)
};

#endif
