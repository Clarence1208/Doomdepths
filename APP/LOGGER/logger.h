//
// Created by Clarence Hirsch on 03/11/2023.
//

#ifndef DOOMDEPTHS_LOGGER_H
#define DOOMDEPTHS_LOGGER_H

// Log levels
typedef enum {
    DEBUG,
    INFO,
    ERROR
} LogLevel;


void initLogger(const char *filename);

void logNewSession();

// Function to log messages
void logMessage(LogLevel level, const char *format, ...);

// Function to close the logger
void closeLogger();

#endif //DOOMDEPTHS_LOGGER_H
