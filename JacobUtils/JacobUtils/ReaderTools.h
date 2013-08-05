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
    void GetListFromFile(const std::string& path, std::vector<std::string>& elements);
    void GetListFromFile(const std::string& path, std::vector<float>& elements);
    

    /**
     * @brief Construct a vector of items from slices of a space separated string
     * 
     * @param inputString
     *     Input string
     * @return
     *     A vector of strings made up of elements from the string
     */
    std::vector<std::string> GetListFromString(const std::string& inputString);

    /**
     * @brief Get a vector from XML file
     *
     * @param inputFile
     *     Input File
     * @param listName
     *     Name of list
     * @return
     *     Vector of strings
     */
    std::vector<std::string> GetListFromXML(const std::string& inputFile,
                                            const std::string& listName);

    /**
     * @brief Return a concatenated vector of strings as a comma-separated string
     *
     * @param inputFile
     *        Name of file
     * @param listName
     *        Name of list
     * @return 
     *     Concatenated string       
     */
    std::string GetStringFromFileXML(const std::string& inputFile, const std::string& listName);
};

#endif // END READERTOOLS_H_
