/// A selection of reader tools to help parse text files
/// For reading in branch lists and/or trigger lists

#ifndef READERTOOLS_H_
#define READERTOOLS_H_ 1

#include <vector>
#include <string>

namespace RT
{
    /**
     * @brief Constructs a vector of items from a text file.
     * One line per element to be put in the vector
     * 
     * @param inputFile
     *     Input text file
     * @return
     *     A vector of strings made up of elements from the text file 
     */
    int GetListFromFile(const std::string& path, std::vector<std::string>& elements);
    int GetListFromFile(const std::string& path, std::vector<float>& elements);
    

    /**
     * @brief Construct a vector of items from slices of a space separated string
     * 
     * @param inputString
     *     Input string
     * @return
     *     A vector of strings made up of elements from the string
     */
    std::vector<std::string> GetListFromString(const std::string& inputString);
};

#endif // END READERTOOLS_H_
