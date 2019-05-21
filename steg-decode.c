// steg-decode.c
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1
// Desifrovanie skrytej spravy, ktora je ulozena ve formate .ppm
// Skryta sprava je ukoncena znakom '/0'


#include "bit_array.h"
#include "eratosthenes.h"
#include "ppm.h"
#include "error.h"
#include <limits.h>
#include <ctype.h>


int secret(const char *filename);

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		warning_msg("Nevhodny format parameter\n");
		return -1;
	}

	secret(argv[1]);
	return 0;
}

int secret(const char *filename)
{
	struct ppm *image;
	unsigned long pocet_char;
	char letter[2]={'\0'};
	int letter_index=0;
	int bit;
	char test;
	unsigned long *array; //pole indexov

	image = ppm_read(filename);
	if (image == NULL)
	{
        	error_msg("Chyba pri nacitani suboru.\n");
	}	

	pocet_char=3* image->xsize * image->ysize;
	array= (unsigned long *) calloc(pocet_char,1);//alokacia
	//overenie alokacie + chybova hlaska
	if (array == NULL)
	{
		error_msg("Subor sa nepodarilo nacitat.\n");	
	}

	array[0]=pocet_char;//ulozenie velkosti pola na 0. prvek pole array
	eratosthenes_sito(array);
	
	for (unsigned int i=2; i<pocet_char; i++)
	{
		if(ba_get_bit(array,i) == 0) 
		{
			if((image->data[i] & 1) == 0)//zistenie ci je LSB 1 alebo 0
			{
				bit=0;
			}
			else
			{
				bit=1;
			}
			BA_SET_BIT_(letter,letter_index,bit);//ulozenie bitu na jeho index
		if(letter_index<CHAR_BIT-1) //zistenie ci uz mame cely Byte
		{
			letter_index++;
		}
		else if(letter[1] != '\0')//overenie ci nieje koniec spravy
			 {
					
			 		test=letter[1];
			 		if (isprint(test))
			 		{
					printf("%c",letter[1]);//ak je znak tlacitelny vytlaci ho
					}
					else
					{	
						free(array); 
						free(image);
						error_msg("Netlacitelny znak\n");
					}


			 	letter_index=0;//nastavenie pocitaca indexu na nula
			 }
			 else
			 {
			 	printf("\n");
			 	break;
			 }
		}	 
			
	}
	if (letter[1] != '\0')
	{
		free(array); 
		free(image); 
		error_msg("Sprava nebola korektne ukoncena\n");
	}
	free(array);
	free(image); 
	return 0;
}


