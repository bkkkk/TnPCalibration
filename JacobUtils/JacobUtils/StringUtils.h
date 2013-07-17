#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_ 1

#include <string>
#include <vector>

namespace SU
{
    /// Concatenate String from string + float + float
    /// @variable var Variable name "pT"
    /// @variable min Bottom of slice
    /// @variable max Top of slice
    /// @return     Concatenated string
    std::string ConcString(std::string var, float min, float max);

    /// Get name of variable for this slice
    /// @variable sliceStr Slice string e.g. "pt_10_20"
    /// @return     Name of variable e.g. "pt"
    std::string GetVarName(std::string sliceStr);

    /// Get low end of slice
    /// @variable sliceStr Slice string e.g. "pt_10_20"
    /// @return     Min of slice e.g. 10
    float GetSliceMin(std::string sliceStr);

    /// Get high end of slice
    /// @variable sliceStr Slice string e.g. "pt_10_20"
    /// @return     Max of slice e.g. 20
    float GetSliceMax(std::string sliceStr);
};


#endif
