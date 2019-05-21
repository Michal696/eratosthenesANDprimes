// error.h
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...); 
void error_msg(const char *fmt, ...);

#endif
