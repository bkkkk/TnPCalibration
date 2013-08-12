#include "MuonEfficiency/ScaleFactorPlotter.h"

#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"

#include "JacobUtils/LoggingUtility.h"

//______________________________________________________________________________
ScaleFactorPlotter::
ScaleFactorPlotter(const std::string& name)
 : fName(name)
{

}

//______________________________________________________________________________
ScaleFactorPlotter::
~ScaleFactorPlotter(void)
{

}

//______________________________________________________________________________
void ScaleFactorPlotter::
Add(const std::string& periodName, TFile* file, int color)
{
  if(periodName.empty() == true)
  {
    LOG_ERROR() << "Period name is empty";
    throw;
  }

  if(file == NULL)
  {
    LOG_ERROR() << "File is not configured correctly";
    throw;
  }

  PeriodInput tempInput;
  tempInput.name = periodName;
  tempInput.file = file;
  tempInput.color = color;

  Add(tempInput);

  return;
}

//______________________________________________________________________________
void ScaleFactorPlotter::
Add(PeriodInput input)
{
  if(input.name.empty() == true)
  {
    LOG_ERROR() << "Period name is empty";
    throw;
  }

  if(input.file == NULL)
  {
    LOG_ERROR() << "File is not configured correctly";
    throw;
  }

  if( fPeriodMap.find ( input.name ) == fPeriodMap.end() )
  {
    fPeriodMap[input.name] = input;
  } else
  {
    LOG_WARNING() << "Period " << input.name << " already in collection";
  }

  return;
}

//______________________________________________________________________________
void ScaleFactorPlotter::
Draw(const std::string& histogramName)
{
  // Output name
  std::string outputName = fName + "_" + histogramName;

  // 
  TCanvas c1(outputName.data(), "");
  THStack stack(outputName.data(), "");

  std::map<std::string, PeriodInput>::const_iterator itr = fPeriodMap.begin();

  // Loop over periods and plot, add to stack and plot things
  for(; itr != fPeriodMap.end(); itr++)
  {
    std::string periodName = (*itr).second.name;
    TFile* file = (*itr).second.file;
    int color = (*itr).second.color;

    LOG_DEBUG1() << periodName << " with color: " << color;

    TObject* obj = file->Get(histogramName.data());

    if( obj == 0 )
    {
      LOG_ERROR() << "Histogram " << histogramName << " not found!!";
      throw;
    }

    TH1F* histo;

    try
    {
      histo = dynamic_cast<TH1F*> (obj);
    } catch (const std::exception& e)
    {
      LOG_ERROR() << "Object NOT a histogram";
      throw;
    }

    // Setting up colors
    histo->SetLineColor(color);
    histo->SetMarkerColor(color);

    stack.Add(histo);
  }

  stack.Draw();
  outputName.append(".png");
  c1.SaveAs(outputName.data(), "png");

  return;
}


