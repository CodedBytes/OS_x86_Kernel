#pragma once
#include "../include/types.h"

#define COLOR_INFO  0x0A  // verde
#define COLOR_WARN  0x0E  // amarelo
#define COLOR_ERR   0x0C  // vermelho
#define COLOR_RESET 0x07  // cinza


static void log_prefix(const char* pfx, u8 color);
void log_info(const char* msg);
void log_warn(const char* msg);
void log_error(const char* msg);