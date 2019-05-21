# makefile
# Řešení IJC-DU1, příklad a) b), 27.3.2017
# Autor: Michal Šajdík, FIT 
# Přeloženo: gcc 6.1.1


CFLAGS=-O2 -std=c99 -Wall -pedantic -lm
.PHONY : clean run
all:  primes-i  primes steg-decode 
 
#sestaveni jednotlivych modulu
primes.o: primes.c bit_array.h eratosthenes.h
	gcc $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	gcc $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

ppm.o: ppm.c ppm.h eratosthenes.h bit_array.h error.h
	gcc $(CFLAGS) -c ppm.c -o ppm.o

error.o: error.c error.h
	gcc $(CFLAGS) -c error.c -o error.o

steg-decode.o: steg-decode.c bit_array.h eratosthenes.h ppm.h
	gcc $(CFLAGS) -c steg-decode.c -o steg-decode.o
#sestaveni jednotlivych programu
primes: eratosthenes.o primes.o error.o
	gcc $(CFLAGS)  eratosthenes.o primes.o error.o -o primes
#nutnost znova zkompilovat eratosthenes.c pre USE_INLINE funckie
primes-i: primes.c error.o eratosthenes.c
	gcc $(CFLAGS) -DUSE_INLINE primes.c  eratosthenes.c error.o -o primes-i

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	gcc $(CFLAGS) steg-decode.o error.o eratosthenes.o ppm.o -o steg-decode

#make run pre porovnanie casu
run:   primes primes-i
	time ./primes  
	time ./primes-i

#vycistenie
clean :
	rm -f *.o
	rm -f primes
	rm -f primes-i
	rm -f steg-decode
