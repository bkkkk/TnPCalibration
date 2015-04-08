#include "./ut_ScaleFactorAttributes.h"

TEST_F(TestSFAttributes, ConstructWithSomeVariables) {
  SFAttributes attribs = SFAttributes::constructScaleFactorWithTitle("test")
                             .withRange(1.2, 4.2)
                             .withYAxisTitle("Scale Factor")
                             .withXAxisTitle("p_{T} [GeV]")
                             .withTitleSize(10)
                             .withTitleOffset(2.4)
                             .withMarkerStyle(21)
                             .withMarkerColor(5);
  EXPECT_EQ(10, attribs.getTitleSize());
  EXPECT_FLOAT_EQ(2.4, attribs.getTitleOffset());
  EXPECT_EQ(5u, attribs.getMarkerColor());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
