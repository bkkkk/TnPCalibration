/**
 * @file
 *
 * @brief Contains a set of macros to facilitate logging
 *
 * The macros included below are part of a logging system that allows the
 * user to control the output of different messages. 
 * Accessing the logging system is done via the LOG(level) macro
 * where level is the logging level of the message or a set of preset
 * logging macro commands.
 * One can set the level to report via SET_LOG_LEVEL macro.
 */

#ifndef LOGGINGUTILITYMACROS
#define LOGGINGUTILITYMACROS 1

/**
 * Log levels
 */
enum ELogLevel {
	kERROR,		/**< Error Level */
	kWARNING,	/**< Warning Level */
	kINFO,		/**< Info Level */
	kDEBUG,		/**< Debug Level */
	kDEBUG1,	/**< Debug1 Level */
	kDEBUG2,	/**< Debug2 Level */
	kDEBUG3,	/**< Debug3 Level */
	kDEBUG4		/**< Debug4 Level */ 
};

#define LOG(level) \
		if (level > LoggingUtility::ReportingLevel()) ; \
		else LoggingUtility().print(level)

#define LOG_ERROR() \
			LOG(kERROR)

#define LOG_WARNING() \
			LOG(kWARNING)

#define LOG_INFO() \
			LOG(kINFO)

#define LOG_DEBUG() \
			LOG(kDEBUG)

#define LOG_DEBUG1() \
			LOG(kDEBUG1)

#define LOG_DEBUG2() \
			LOG(kDEBUG2)

#define LOG_DEBUG3() \
			LOG(kDEBUG3)

#define LOG_DEBUG4() \
			LOG(kDEBUG4)

/** 
 * Macro to set log level
 */
#define SET_LOG_LEVEL(level) \
		LoggingUtility::ReportingLevel() = level

#endif
