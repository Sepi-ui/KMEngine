#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "logIt.h"

//Define stream Array
static FILE* log_stream[COUNT_LOG];
//Set output for different types
void initializeLogStreams() {
	log_stream[FATAL_LOG] = stderr;
	log_stream[ERROR_LOG] = stderr;
	log_stream[WARNING_LOG] = stderr;
	log_stream[DEBUG_LOG] = stderr;
	log_stream[TRACE_LOG] = stderr;
	log_stream[INFO_LOG] = stdout;
	log_stream[PERFORMANCE_LOG] = stderr;
	log_stream[UNIT_LOG] = stdout;
}

void log_message(FILE* stream, const char* logType, const char* format, va_list args) {
	// Print [TYPE]
	fprintf(stream, "%s ", logType);
	//Print Message
	vfprintf(stream, format, args);
	//Print errno if available
	if (errno != 0) {
		fprintf(stream, "%s\n", strerror(errno));
		};
}

void fatal_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[FATAL_LOG], "[FATAL]", format, args);
	va_end(args);
}
void error_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[ERROR_LOG], "[ERROR]", format, args);
	va_end(args);
}
void warning_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[WARNING_LOG], "[WARNING]", format, args);
	va_end(args);
}
void debug_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[DEBUG_LOG], "[DEBUG]", format, args);
	va_end(args);
}

void trace_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[TRACE_LOG], "[TRACE]", format, args);
	va_end(args);
}

void info_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[INFO_LOG], "[INFO]", format, args);
	va_end(args);
}

void performance_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[PERFORMANCE_LOG], "[PERFORMANCE]", format, args);
	va_end(args);
}

void unit_log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	log_message(log_stream[UNIT_LOG], "[UNIT]", format, args);
	va_end(args);
}

void setStream(LogType type, FILE* stream) {
if (type >= COUNT_LOG) {
	fprintf(stderr, "in setStream: Invalid Type passed"); 
	};
if (stream != NULL) {
	log_stream[type] = stream;
	}else {
	log_stream[type] = stderr;
	};
}
