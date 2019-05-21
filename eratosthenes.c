// eratosthenes.c
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "eratosthenes.h"
#include "bit_array.h"
#include  <math.h>



//indexi prvocisiel 0 , ostatne 1
void eratosthenes_sito(bit_array_t pole)
{
    unsigned long limit = (unsigned long) sqrt(pole[0]);   //zistenie odmocniny 
    unsigned long n = 1;
    ba_set_bit(pole,0,1);  //nastavenie 0. indexu na 1
    ba_set_bit(pole,1,1);  //nastavenie 1. indexu na 1
    
    for (unsigned long i = 2; i <= limit; i++)
    {
        if (ba_get_bit(pole,i) == 0)     //najde prvocislo
        {
            while ( n*i < pole[0])     
            {
                ba_set_bit(pole, n*i, 1); //nasobky prvocisla = 1
                n++; 
            }
            n = i;
        }
    }
   ba_set_bit(pole,2,0);  //nastavenie 2. indexu na 0 //je to prvocislo
}
