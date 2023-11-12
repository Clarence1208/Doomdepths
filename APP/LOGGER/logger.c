#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "logger.h"

// Global file pointer for the log file
FILE *logFile;

// Function to log messages with a timestamp and log level
void logMessage(LogLevel level, const char *format, ...) {
    if (logFile == NULL) {
        fprintf(stderr, "Logger not initialized. Call initLogger() first.\n");
        return;
    }

    const char *levelStr;
    switch (level) {
        case DEBUG:
            levelStr = "DEBUG";
            break;
        case INFO:
            levelStr = "INFO";
            break;
        case ERROR:
            levelStr = "\x1b[31mERROR\x1b[0m"; // Red text for error
            break;
        default:
            levelStr = "UNKNOWN";
    }

    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    va_list args;
    va_start(args, format);

    fprintf(logFile, "[%02d-%02d-%04d %02d:%02d:%02d] [%s] ", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
            tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, levelStr);
    vfprintf(logFile, format, args);
    fprintf(logFile, "\n");
    fflush(logFile); // Ensure the log is written immediately

    va_end(args);
}

void logNewSession() {
    time_t current_time;
    struct tm* time_info;

    // Get the current time
    time(&current_time);

    // Convert the current time to a struct tm for more details
    time_info = localtime(&current_time);
    char* newSessionMessage = malloc(sizeof(char) * 100);
    sprintf(newSessionMessage, "\n\nNew session started at %02d-%02d-%04d %02d:%02d:%02d", time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

    fprintf(logFile, "%s\n", newSessionMessage);
    fflush(logFile); // Ensure the log is written immediately
}

// Function to initialize the logger
void initLogger(const char *filename) {
    logFile = fopen(filename, "a+");
    if (logFile == NULL) {
        perror("Error opening log file");
    }
    logNewSession();
}

// Function to close the logger
void closeLogger() {
    if (logFile != NULL) {
        fclose(logFile);
        logFile = NULL;
    }
}
