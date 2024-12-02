#ifndef LOG_H_
#define LOG_H_
#include"stdint.h"
#include"stdio.h"
#define LOG(X) printf("%s\n",X);

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void logInit(); 

#endif