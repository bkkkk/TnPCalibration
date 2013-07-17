#ifndef LOGGINGUTILITY_H_
#define LOGGINGUTILITY_H_

#include "LoggingUtilityMacros.h"

#include <sstream>
#include <string>
#include <stdio.h>

/**
 * @class LoggingUtility
 *
 * @brief A logging system with customizable logging levels
 *
 * A logging system that allows the user to control the output of different
 * messages. Accessing the logging system is done via the LOG(level) macro
 * where level is the logging level of the message. One can set the level
 * to report via SET_LOG_LEVEL macro.
 */
class LoggingUtility
{

	/**
	 * Public default ctor
	 *
	 * This function is usually NOT called directly as this circumvents
	 * the log level check. 
	 */
	public:
		LoggingUtility(void);

	/**
	 * Dtor
	 * 
	 * This flushes the stream object causing the output to screen
	 */
	public:
		virtual ~LoggingUtility(void);

	/**
	 * Function to access output stream using <<operator
	 * 
	 * @param level
	 *    Logging Level ELogLevel for the acceptable arguements
	 * @return
	 *    osringstream object
	 */ 
	public:
		std::ostringstream&
		print(ELogLevel level = kINFO);

	private:
		std::ostringstream
		os; /**< Output stream */
	
	private:
		static ELogLevel 
		reportingLevel; /**< Holds the current reporting level */

	/**
	 * cctor should not be used
	 */
	private:
		LoggingUtility(const LoggingUtility&);

	/**
	 * cctor also not used
	 */
	private:
		LoggingUtility&
		operator =(const LoggingUtility&);

	/**
	 * Returns a reference to the static Logging level. See #ELogLevel for more information.
	 * Can be used to set #reportingLevel
	 * 
	 * @return
	 *    Logging level.
	 */
	public:
		static ELogLevel&
		ReportingLevel(void);

	/**
	 * Convert #ELogLevel to a string
	 * 
	 * @param level
	 *    Log level. See #ELogLevel for more information.
	 * @return
	 *    String with name of
	 */
	public:
		static std::string
		ToString(ELogLevel level);

	/**
	 * Convert string to ELogLevel. See #ELogLevel for more information
	 * 
	 * @param level
	 *    Convert a string with log level name to ELogLevel
	 * @return
	 *    Log level
	 */
	public:
		static ELogLevel
		FromString(const std::string& level);

  /**
   * Returns a special string that colorizes terminal output
   * 
   * @param color
   *     A string that defines the formatting string to return
   * @return
   *     Appropriate string to colorize terminal output
   */
  public:
    const std::string&
    Color( const std::string& color );

  /**
   * Returns the 
   *
   */
  public:
    std::string
    SetColor(ELogLevel level);

	/**
	 * Get time and date for logging
	 * 
	 * @return
	 *    A string of formatted time and date
	 */
	private:
		std::string
		TimeNow(void);

};
#endif

