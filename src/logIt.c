#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
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

LogBuffer* initialize_log_buffer(size_t initialSize) {
LogBuffer* buffer = malloc(sizeof(LogBuffer));
if (buffer == NULL) {
	error_log("could not initialize LogBuffer\n");
	return NULL;
	};
buffer->data = malloc(initialSize);
if (buffer->data == NULL) {
	error_log("could not allocate memory for data in LogBuffer\n");
	};
buffer->size = initialSize;
buffer->used = 0;
return buffer;
}

void buffer_log(LogBuffer* buffer, const char* format) {
va_list args;
va_start(args, format);

int newEntrySize = vsnprintf(NULL, 0, format, args) + 1;
va_end(args);

if (buffer->used + newEntrySize > buffer->size) {
	size_t newSize = buffer->size * 2;
	while (newSize < buffer->used + newEntrySize) {
		newSize *= 2;
		};
	char* newData = realloc(buffer->data, newSize);
	if (newData == NULL) {
		error_log("could not resize LogBuffer->data");
		return;
		};
	buffer->data = newData;
	buffer->size = newSize;
	};

va_start(args, format);
vsnprintf(buffer->data + buffer->used, newEntrySize, format, args);
va_end(args);
buffer->used += newEntrySize -1;//-1 to remove null terminator
};


void write_buffer_to_file(LogBuffer buffer, const char* filename) {

FILE* file = fopen(filename, "w");
	if (file == NULL) {
	error_log("could not open Log file");
	exit(EXIT_FAILURE);
	};
fwrite(buffer->data, 1, buffer->used, file);
fclose(file);
}

void free_log_buffer() {
free(buffer->data);
free(buffer);
}
