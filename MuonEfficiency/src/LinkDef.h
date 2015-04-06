#include <MuonEfficiency/PileupPRW.h>
#include <MuonEfficiency/SampleHistograms.h>
#include <MuonEfficiency/EfficiencyMaker.h>
#include <MuonEfficiency/SingleGausFit.h>
#include <MuonEfficiency/FitResults.h>
#include <MuonEfficiency/HistogramFactory.h>
#include <MuonEfficiency/TnPSlices.h>
#include <MuonEfficiency/SummaryPlotMaker.h>
#include <MuonEfficiency/EventWeighting.h>
#include <MuonEfficiency/Weighting.h>
#include <MuonEfficiency/PileupReWeighting.h>

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;

#pragma link C++ class SampleHistograms+;
#pragma link C++ class SingleGausFit+;
#pragma link C++ class FitResults+;
#pragma link C++ class HistogramFactory+;
#pragma link C++ class TnPSlices+;
#pragma link C++ class SummaryPlotMaker+;
#pragma link C++ class EventWeighting+;
#pragma link C++ class PileupReWeighting+;
#pragma link C++ class Weighting+;
#pragma link C++ class std::vector<std::pair<float, float> >+;
#pragma link C++ class std::map<std::string, std::vector<std::pair<float, float> > >+;
#pragma link C++ class std::map<std::string, std::vector<float> >+;
#pragma link C++ class PileupPRW+;

#ifdef DEPRECATED 
#pragma link C++ class EfficiencyMaker+;
#endif
