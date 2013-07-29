// Add Sample to XML file
// Get List of samples from XML file
// Get element of samples XML file

#include "JacobUtils/SampleList.h"

int main( int args, char** argv )
{
  ST::SampleList* list = new ST::SampleList("XMLRepository.xml");

  // Get Path of sample that isn't there
  list->GetPath("PeriodA");

  // Add Path of sample
  list->AddSample("PeriodA", "Path");
  list->Write();

  // Print list of samples
  list->Print();

  // Get path
  list->GetPath("PeriodA");
}
