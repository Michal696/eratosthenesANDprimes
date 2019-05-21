// bit_array.h
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1


#include <limits.h>
#include "error.h"

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

typedef unsigned long bit_array_t[];



#define unsigned_long_bits(velikost) ((velikost) % (sizeof(unsigned long) * CHAR_BIT) == 0 ? (velikost) / (sizeof(unsigned long) * CHAR_BIT) : (velikost) / (sizeof(unsigned long) * CHAR_BIT) +1)

#define celocis_typ(celociselny_typ) (sizeof((celociselny_typ)[0]) * CHAR_BIT)
//vytvorenie pola o danej velikosti
#define ba_create(jmeno_pole, velikost)  unsigned long (jmeno_pole)[1 + unsigned_long_bits(velikost)] = {(unsigned long)(velikost)}
//pomocne makro pre zistenie bitu
#define BA_GET_BIT_(jmeno_pole, index) ( ((jmeno_pole)[1 +(index)/celocis_typ(jmeno_pole)] & ((unsigned long)1 << (index) % celocis_typ(jmeno_pole))) > 0 ? 1 : 0 )
//pomocne makro pre  natavenie bitu na index	
#define BA_SET_BIT_(jmeno_pole,index,vyraz) (vyraz) != 0 ? ((jmeno_pole)[1 +(index) / celocis_typ(jmeno_pole)] |= (unsigned long)1 << (index) % celocis_typ(jmeno_pole))  : ((jmeno_pole)[1 +(index) / celocis_typ(jmeno_pole)] &= ~((unsigned long)1 << (index) % celocis_typ(jmeno_pole)))


//
#ifndef INLINE 
//makra


#define ba_size(jmeno_pole) ((jmeno_pole)[0])
// nastavenie bitu na index
#define ba_set_bit(jmeno_pole,index,vyraz) ((unsigned long)index) >= (jmeno_pole)[0] ? error_msg("Index : %lu je mimo pola ktore ma :%lu setbit\n", (index),(jmeno_pole)[0]),0 : (BA_SET_BIT_(jmeno_pole,(index),(vyraz)))
// zistenie bitu na danom indexi
#define ba_get_bit(jmeno_pole,index) (index) >= (jmeno_pole)[0] ? error_msg("Index : %lu je mimo pola ktore ma :%lu getbit\n", (unsigned long) index,(unsigned long)(jmeno_pole)[0]),0 : (BA_GET_BIT_(jmeno_pole,(index)))


#else 
//inline
inline unsigned long ba_size(bit_array_t jmeno_pole)
{
	return jmeno_pole[0];
}


// ziska hodnotu
inline int ba_get_bit(bit_array_t jmeno_pole,unsigned long index)
{
	if (index >= jmeno_pole[0])
	{
		error_msg("Index : %lu je mimo pola ktore ma :%lu setbit\n", (index),(jmeno_pole)[0]);
	}

		
	return ( (jmeno_pole[1 +(index)/celocis_typ(jmeno_pole)] & ((unsigned long)1 << (index)%celocis_typ(jmeno_pole))) != (unsigned long)0 ? 1 : 0 );
}


// ulozi hodnotu do daneho indexu, pre 1 ulozi 1 , pre ine cislo 0 
inline void ba_set_bit(bit_array_t jmeno_pole,unsigned long index,int vyraz)
{
	if (index >= jmeno_pole[0])
	{
		error_msg("Index : %lu je mimo pola ktore ma :%lu setbit\n", (index),(jmeno_pole)[0]);
	}
	if (vyraz == 1)
	{
		//nastavenie 1
		(jmeno_pole[1 +(index)/celocis_typ(jmeno_pole)] &= ~((unsigned long)1 << (index)%celocis_typ(jmeno_pole)));
	}
	else
	{	
		//nastavenie 0
		(jmeno_pole[1 +(index)/celocis_typ(jmeno_pole)] |= (unsigned long)1 << (index)%celocis_typ(jmeno_pole));
	}
}	

#endif
#endif
