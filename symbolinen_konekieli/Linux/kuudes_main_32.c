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
void set_method(int m);

static const char FPU_USED[] = "x87";
static const char SSE_USED[] = "SSE";
static const char *method = FPU_USED;

int main(void)
{
   double ala = laske_ala(5.0);
   printf("%s: Ympyrän ala = %f\n", method, ala);

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
//-------------------------
void set_method(int m)
{
   method = m ? SSE_USED: FPU_USED;
}

