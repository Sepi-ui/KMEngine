#ifndef LOGIT_H
#define LOGIT_H
#include <stdbool.h>

typedef enum {
	FATAL_LOG,
	ERROR_LOG,
	WARNING_LOG,
	DEBUG_LOG,
	TRACE_LOG,
	INFO_LOG,
	PERFORMANCE_LOG,
	UNIT_LOG,
	COUNT_LOG
}LogType;

void initializeLogStreams();

void fatal_log(const char* format, ...);
void error_log(const char* format, ...);
void warning_log(const char* format, ...);
void debug_log(const char* format, ...);
void trace_log(const char* format, ...);
void info_log(const char* format, ...);
void performance_log(const char* format, ...);
void unit_log(const char* format, ...);
void setStream(LogType type, FILE* stream);

#endif
