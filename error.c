// error.c
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "error.h"

void warning_msg(const char *fmt, ...)
{
    fprintf(stderr,"CHYBA: ");
    va_list arg;        
    va_start(arg, fmt);
    vfprintf(stderr, fmt, arg);
    va_end(arg);
}

void error_msg(const char *fmt, ...)
{
    fprintf(stderr, "CHYBA: ");
    va_list arg;
    va_start(arg, fmt);
    vfprintf(stderr, fmt, arg);
    va_end(arg);

    exit(1);
}
