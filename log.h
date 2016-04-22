/*
 * log.h
 *
 *  Created on: 30/06/2013
 *      Author: anibal
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define RES_OK 0
#define RES_OUT_OF_MEMORY -1
#define RES_FILE_NOT_FOUND -2

typedef enum LOG_LEVEL {
	trace, debug, info, warn, error, fatal
} LoggerLevel;


#define DEFAULT_FILES_TO_KEEP 1
#define DEFAULT_FILE_SIZE 10*1024*1024 /* default is 10 MB */

typedef struct Logger {
	char* path;
	FILE* output;
	LoggerLevel level;
	size_t maxFileSize;
	unsigned char filesToKeep;
} Logger;

int logCreate(Logger* logger, char* filepath, LoggerLevel level, size_t fileSizeLimit, unsigned char filesToKeep);

int logLightInit(Logger* logger, char* filepath, LoggerLevel level);

void setFileSizeLimit(Logger* logger, size_t bytes);

void setFilesToKeep(Logger* logger, unsigned char files);

void logTrace(Logger* logger, char* msg);

void logDebug(Logger* logger, char* msg);

void logInfo(Logger* logger, char* msg);

void logWarn(Logger* logger, char* msg);

void logError(Logger* logger, char* msg);

void logFatal(Logger* logger, char* msg);

void logClose(Logger* logger);

#endif /* LOG_H_ */
