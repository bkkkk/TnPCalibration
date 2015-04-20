#include "JacobUtils/SampleList.h"

int main() {
  ST::SampleList* list = new ST::SampleList("XMLRepository.xml");
  list->GetPath("PeriodA");
  list->AddSample("PeriodA", "Path");
  list->Write();
  list->Print();
  list->GetPath("PeriodA");

  return (0);
}
