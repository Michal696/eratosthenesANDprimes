// primes.c
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1
//vypis poslednych 10 prvocisiel z intervalu od 0 po MAX_LIMIT
#include <stdio.h>
#include <stdlib.h>

#include "bit_array.h"
#include "eratosthenes.h"
#include "error.h"

//nastavenie MAX_LIMIT a PRINT_NUMBER
#define MAX_LIMIT 303000000     
#define PRINT_NUMBER 10      
void prime_numbers();


int main()
{
	prime_numbers();
	return 0;
}


void prime_numbers()
{
	ba_create(bit_array,(MAX_LIMIT));	//vytvori bitove pole
	eratosthenes_sito(bit_array); 	//nastavi prvociselne indexy na 0, ostatne indexy na 1
	int count=0;
	unsigned long i;
	for (i =MAX_LIMIT-1; count<PRINT_NUMBER; --i) //prehladava z vrchu na dol dokial nenajde "PRINT_NUMBER" prvocisiel
	{
		if (ba_get_bit(bit_array,(i)) == 0) //najdenie prvocisla
		{
			count++;	//pocet najdenych prvocisiel
		}
	}

	//vypis prvocisiel vzestupne
	for (unsigned long j=i;j<=MAX_LIMIT-1;++j)
	{
		if (ba_get_bit(bit_array,(j)) == 0)
		{
			printf("%lu\n",j);
		}
	}
}

