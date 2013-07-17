#include <TruthNavigationTools/TruthTools.h>
#include <string>
#include <iostream>

int main()
{
  
  std::cout << "Running test of Truth Tools" << std::endl;
  std::string electronName = TT::GetParticleName(11);
  std::cout << "This should read e: " << electronName << std::endl;

  electronName = TT::GetParticleName(200);
  std::cout << "This should read 200: " << electronName << std::endl;

  electronName = TT::GetParticleName(-11);
  std::cout << "This should read e: " << electronName << std::endl;

  std::vector<int> testSiblings;
  testSiblings.push_back(10);
  testSiblings.push_back(11);
  testSiblings.push_back(23);

  TT::PrintParticleInformation(0, 11, 3, 132.2, 2.3, testSiblings, testSiblings);
  TT::PrintParticleInformation(1, 11, 2, 100.2, 2.5, testSiblings);
}