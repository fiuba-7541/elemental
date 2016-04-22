/*
 * log.c
 *
 *  Created on: 30/06/2013
 *      Author: anibal
 */

#include "log.h"

int logLightInit(Logger* logger, char* filepath, LoggerLevel level) {
	logger->path = (char*) malloc(sizeof(char) * (strlen(filepath) + 1));
	if (!logger->path) {
		return RES_OUT_OF_MEMORY;
	}

	logger->output = fopen(filepath, "a+t");
	if (!logger->output) {
		free(logger->path);
		return RES_FILE_NOT_FOUND;
	}

	strcpy(logger->path, filepath);
	logger->level = level;
	logger->filesToKeep = DEFAULT_FILES_TO_KEEP;
	logger->maxFileSize = DEFAULT_FILE_SIZE;
	return RES_OK;
}

int logCreate(Logger* logger, char* filepath, LoggerLevel level, size_t fileSizeLimit, unsigned char filesToKeep) {
	int initRes = logLightInit(logger, filepath, level);
	if (initRes != RES_OK) {
		return initRes;
	}
	logger->filesToKeep = DEFAULT_FILES_TO_KEEP;
	logger->maxFileSize = DEFAULT_FILE_SIZE;
	return RES_OK;
}

void setFileSizeLimit(Logger* logger, size_t bytes) {
	logger->maxFileSize = bytes;
}

void setFilesToKeep(Logger* logger, unsigned char files) {
	logger->filesToKeep = files;
}

void checkFileSize(Logger* logger) {
	// TODO verify the file size and chop it in case it grew too large.
}

void printMsg(FILE* output, LoggerLevel logLevel, LoggerLevel msgLevel, char* label, char* msg) {
	if (logLevel <= msgLevel) {
		fprintf(output, "[%s] %s\n", label, msg);
	}
}

void logTrace(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, trace, "TRACE", msg);
}

void logDebug(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, debug, "DEBUG", msg);
}

void logInfo(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, info, "INFO", msg);
}

void logWarn(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, warn, "WARN", msg);
}

void logError(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, error, "ERROR", msg);
}

void logFatal(Logger* logger, char* msg) {
	checkFileSize(logger);
	printMsg(logger->output, logger->level, fatal, "FATAL", msg);
}

void logClose(Logger* logger) {
	fclose(logger->output);
	free(logger->path);
}


