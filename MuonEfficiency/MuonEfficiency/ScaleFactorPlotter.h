#ifndef SCALEFACTORPLOTTER_H_
#define SCALEFACTORPLOTTER_H_ 1

#include <string>
#include <map>

class TH1F;
class TFile;

/**
 * @class ScaleFactorPlotter
 */
class ScaleFactorPlotter
{
  /**
   * @class PeriodInputObject
   */
  struct PeriodInput {
    std::string name;
    TFile* file;
    int color;
  };

public:
  /**
   * Default constructor for scale factor plotter
   * @param  name  Name of plotter, used in the output when saving files
   */
  explicit ScaleFactorPlotter(const std::string& name = "ScaleFactorPlotter");
 
public:
  /**
   * Dtor
   */
  ~ScaleFactorPlotter(void);

public:
  void Add(const std::string& periodName, TFile* file, int color);

public:
  /**
   * Add a period to the plotting scheme
   * @param input Input object containing the period information
   */
  void Add(PeriodInput input);

public:
  /**
   * Draw and Save the histogram with all periods added
   * @param options Drawing options to pass to TH1::Draw()
   */
  void Draw(const std::string& histogramName);

private:
  std::string fName; //< Name of object used in output filename
  std::map<std::string, PeriodInput> fPeriodMap; //< Period Map holding period info
};

#endif