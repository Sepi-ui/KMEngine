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

typedef struct LogBuffer {
	char* data;
	size_t size;
	size_t used;
}LogBuffer;

void initializeLogStreams();
LogBuffer*  initialize_log_buffer(size_t initialSize);

void fatal_log(const char* format, ...);
void error_log(const char* format, ...);
void warning_log(const char* format, ...);
void debug_log(const char* format, ...);
void trace_log(const char* format, ...);
void info_log(const char* format, ...);
void performance_log(const char* format, ...);
void unit_log(const char* format, ...);
void buffer_log(LogBuffer* buffer, const char* format, ...);
void write_buffer_to_file(LogBuffer* buffer, const char* filename);
void free_log_buffer();
void setStream(LogType type, FILE* stream);

#endif
