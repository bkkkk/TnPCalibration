#include <string>
#include <vector>
#include "TruthNavigationTools/ChainNavigationTools.h"
#include "JacobUtils/LoggingUtility.h"
#include <iostream>

//______________________________________________________________________________
TT :: ChainNavigationTools ::
ChainNavigationTools(const D3PDReader::TruthParticleD3PDObject& mc)
 : sink(mc)
{ };

//______________________________________________________________________________

//______________________________________________________________________________
void TT :: ChainNavigationTools ::
PrintParentChain(const size_t index)
{
  TT::PrintParticleInformation(sink[index], true);

  LOG_INFO() << "Index " << index << " which has " << sink[index].parent_index().size() << " parents";

  for(size_t parentIdx = 0; parentIdx != sink[index].parent_index().size(); parentIdx++)
  {
    PrintParentChain(sink[index].parent_index()[parentIdx]);
  }
};

//______________________________________________________________________________
void TT::ChainNavigationTools::PrintChildChain(const size_t index)
{
  TT::PrintParticleInformation(sink[index], true);

  LOG_INFO() << "Index " << index << " which has " << sink[index].child_index().size() << " children";

  for(size_t childIdx = 0; childIdx != sink[index].child_index().size(); childIdx++)
  {
    PrintChildChain(sink[index].child_index()[childIdx]);
  }
};

//______________________________________________________________________________
void TT :: ChainNavigationTools ::
PrintSiblingChain(const size_t index, const siblingType type)
{
  std::string siblingName = GetNameOfSibling(type);
  
  LOG_INFO() << "Printing chain of " << siblingName << " for index " << index;
  

  if(type == PARENT)
  {
    PrintParentChain(index);
  }
  else
  {
    PrintChildChain(index);
  }
};

//______________________________________________________________________________
void TT :: ChainNavigationTools ::
PrintAllOfType(const int& pdgId)
{
  for(int mcIdx = 0; mcIdx != sink.n(); mcIdx++)
  {
    if(sink[mcIdx].pdgId() == pdgId || sink[mcIdx].pdgId() == -pdgId )
    {
      TT::PrintParticleInformation(sink[mcIdx]);
    };
  };

  return;
};

//______________________________________________________________________________
std::vector<int> TT :: ChainNavigationTools ::
FindAllOfType(const int& pdgId)
{
  std::vector<int> found;

  for(int mcIdx = 0; mcIdx != sink.n(); mcIdx++)
  {
    if(sink[mcIdx].pdgId() == pdgId || sink[mcIdx].pdgId() == -pdgId )
    {
      found.push_back(mcIdx);
    };
  };
  
  return (found);
};

//______________________________________________________________________________
void TT :: ChainNavigationTools ::
PrintAll()
{
  for(int mcIdx = 0; mcIdx!=sink.n(); mcIdx++)
  {
    TT::PrintParticleInformation(sink[mcIdx]);
  };
};

