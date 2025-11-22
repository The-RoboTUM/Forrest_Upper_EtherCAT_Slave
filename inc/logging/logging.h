#ifndef LOGGING_H

#include <stdio.h>

void logger_init(void);
void logger_println(const char* TAG, const char* fmt, ...);

#endif // LOGGING_H
