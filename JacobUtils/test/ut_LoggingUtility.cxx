#include "JacobUtils/LoggingUtility.h"

int main() {
  SET_LOG_LEVEL(kDEBUG4);
  LOG_ERROR() << "This is an error message";
  LOG_WARNING() << "This is a warning message";
  LOG_INFO() << "This is an info message";
  LOG_DEBUG() << "This is a debug message";
  LOG_DEBUG1() << "This is a debug1 message";
  LOG_DEBUG2() << "This is a debug2 message";
  LOG_DEBUG3() << "This is a debug3 message";
  LOG_DEBUG4() << "This is a debug4 message";
  SET_LOG_LEVEL(kINFO);
  LOG_DEBUG() << "If this is showing, something is wrong";
}
