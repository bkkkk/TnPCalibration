#include <iostream>
#include <TnPSelector/TJPsiProbeSelector.h>

int main ()
{
  TJPsiProbeSelector* probeSelector = new TJPsiProbeSelector();
  probeSelector->etaCut = 2.5; probeSelector->pCut = 3000;

  std::cout << "Testing Good probe" << std::endl;
  if(probeSelector->accept(2.2, 4000) != 0)
  {
    std::cout << "TJPsiProbeSelector is performing as expected" << std::endl;
  } else
  {
    std::cout << "TJPsiProbeSelector is NOT working correctly" << std::endl;
    return(0);
  };

  std::cout << "Testing Bad Eta Probe" << std::endl;
  if(probeSelector->accept(2.9, 10000) != 1)
  {
    std::cout << "TJPsiProbeSelector is performing as expected" << std::endl;
  } else
  {
    std::cout << "TJPsiProbeSelector is NOT working correctly" << std::endl;
    return(0);
  };

  std::cout << "Testing Bad P Probe" << std::endl;
  if(probeSelector->accept(2.2, 0) != 1)
  {
    std::cout << "TJPsiProbeSelector is performing as expected" << std::endl;
  } else
  {
    std::cout << "TJPsiProbeSelector is NOT working correctly" << std::endl;
    return(0);
  };

  return(1);
};
