#include <stdlib.h>
#include <stdio.h>

/* asm funktiot */
extern void sotke(const char *);

static const char suojattu[] = "ei voi muokata";

int main(void)
{

   printf("C main: alkuperäinen teksti: %s\n", suojattu);
   sotke(suojattu);
   printf("C main: teksti nyt: %s\n", suojattu);

   printf("Ohjelma suoritettu.\n");

   return EXIT_SUCCESS;
}

