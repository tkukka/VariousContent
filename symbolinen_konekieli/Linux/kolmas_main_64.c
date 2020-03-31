#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*             tietotyyppien koot tavuina
               ==========================
               int    long    size_t    tyyppi *ptr
i386/32-bit    4       4       4          4
x86_x64        4       8       8          8

*/


/* asm funktiot */
extern double laske_ala(double);
extern const char* muunna(unsigned long int*);

void reset_errno(void);
int get_errno(void);

int main(void)
{
   double ala = laske_ala(5.0);
   printf("SSE: Ympyrän ala = %f\n", ala);

   unsigned long arvo = 99999;      //onnistuessaan pitäisi vaihtua
   const char *ptr = muunna(&arvo);
   char *end = NULL;

   if (ptr)
   {
      printf("Asm: Merkkijono '%s' lukuna: %lu.\n", ptr, arvo);
      errno = 0;
      arvo = strtoul(ptr, &end, 10);

      if ((errno == 0) && (end != ptr) && (*end == '\0') )
      {
         printf("C main(): toiminnan vertailu. '%s' lukuna: %lu\n", ptr, arvo);
      }
      else
      {
         printf("'%s' muuntaminen ei onnistunut.\n", ptr);
      }
   }
   else
   {
      printf("Muunnos epäonnistui.\n");
   }

   printf("Ohjelma suoritettu.\n");

   return EXIT_SUCCESS;
}
//-------------------------
void reset_errno(void)
{
   errno = 0;
}
//-------------------------
int get_errno(void)
{
   return errno;
}

