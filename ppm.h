// ppm.h
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1
#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>

#include "eratosthenes.h"
#include "bit_array.h"
#include "error.h"

struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);
//zapisanie struktury do suboru
int ppm_write(struct ppm *p, const char * filename);

#endif
