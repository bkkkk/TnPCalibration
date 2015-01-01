#ifndef TJPSITAGSELECTOR_TEST_H_
#define TJPSITAGSELECTOR_TEST_H_ 1

#include <cpptest.h>

class TJPsiTagSelector;

class TestTagSelector : public Test::Suite {
private:
  TJPsiTagSelector* selector;

public:
  TestTagSelector() {
    TEST_ADD(TestTagSelector::testInitializeWithNoParameters)
    TEST_ADD(TestTagSelector::testInitializeWithValidParameters)
    
    TEST_ADD(TestTagSelector::testIndividualCuts)
    TEST_ADD(TestTagSelector::testNumericSelectionOfBadMuon)
    TEST_ADD(TestTagSelector::testNumericSelectionOfGoodMuon)
    
    TEST_ADD(TestTagSelector::testSelectionFromBadMuon)
    TEST_ADD(TestTagSelector::testSelectionFromGoodMuon)
    TEST_ADD(TestTagSelector::testFinalize)
  }

private:
  void testInitializeWithNoParameters();
  void testInitializeWithValidParameters();
  
  void testIndividualCuts();
  void testNumericSelectionOfBadMuon();
  void testNumericSelectionOfGoodMuon();
  
  void testSelectionFromBadMuon();
  void testSelectionFromGoodMuon();
  
  void testFinalize();

protected:
  virtual void setup();
  virtual void tearDown();
};

#endif
/*
  int finalize(void);
*/