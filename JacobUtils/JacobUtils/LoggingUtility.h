#ifndef LOGGINGUTILITY_H_
#define LOGGINGUTILITY_H_

#include "LoggingUtilityMacros.h"

#include <sstream>
#include <string>
#include <stdio.h>

class LoggingUtility {
 public:
  LoggingUtility(void);
  ~LoggingUtility(void);

 private:
  LoggingUtility(const LoggingUtility&);
  LoggingUtility& operator=(const LoggingUtility&);
  std::string TimeNow(void);

 public:
  std::ostringstream& print(ELogLevel level = kINFO);
  static std::string ToString(ELogLevel level);
  static ELogLevel& ReportingLevel(void);
  static ELogLevel FromString(const std::string& level);
  const std::string& Color(const std::string& color);
  std::string SetColor(ELogLevel level);

 private:
  std::ostringstream os;
  static ELogLevel reportingLevel;
};

#endif
