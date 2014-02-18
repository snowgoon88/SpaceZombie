/* -*- coding: utf-8 -*- */

#include <stdio.h>

float fl1[] = {0.0f, 1.0f, -2.0f, 3e-12, -12.2345, 34.21e+15, 0.0f, 1.0f, 10.0f, 100, 100.1f, 100.01f, 100.001f, 100.0001f, 100.00001f, 100.000001f, 100.0000001f};
float fl2[] = {0.0 , 1.0 , -2.0 , 3e-12, -12.2345, 34.21e+15, 0.0 , 1.0 , 10.0 , 100, 100.1 , 100.01 , 100.001 , 100.0001 , 100.00001 , 100.000001 , 100.0000001 };
double dl1[] = {0.0 , 1.0 , -2.0 , 3e-12, -12.2345, 34.21e+15, 0.0 , 1.0 , 10.0 , 100, 100.1 , 100.01 , 100.001 , 100.0001 , 100.00001 , 100.000001 , 100.0000001 };
int nb_fl = 17;

//******************************************************************************
void print_hexa( unsigned char *addr, int length ) 
{
  for( int i = 0; i < length; ++i) {
    printf("%02X",*(addr+i));
  }
}

//******************************************************************************
int main( int argc, char *argv[] )
{ 
  int size_uc = sizeof(unsigned char);
  printf( "sizeof(unsigned char)=%d\n",size_uc);
  int size_us = sizeof(unsigned short);
  printf( "sizeof(unsigned short)=%d\n",size_us);
  int size_ui = sizeof(unsigned int);
  printf( "sizeof(unsigned int)=%d\n",size_ui);
  int size_f = sizeof(float);
  printf( "sizeof(float)=%d\n",size_f);
  int size_d = sizeof(double);
  printf( "sizeof(double)=%d\n",size_d);

  printf( "*** DL1 / FL1 / FL2 = HEXDBL HEXFL11 / HEXFL22\n");
  for(int i=0; i<nb_fl; ++i) {
    printf( "%f / ", dl1[i]);
    printf( "%f / ", fl1[i]);
    printf( "%f = ", fl2[i]);
    print_hexa( (unsigned char *) &(dl1[i]), size_d );
    printf( " " );
    print_hexa( (unsigned char *) &(fl1[i]), size_f );
    printf( " " );
    print_hexa( (unsigned char *) &(fl2[i]), size_f );
    printf( "\n" );
  }

  char header[] ="FLOAT\0\0\0\0\0\0\0\0\0\0";
  FILE *fp = fopen( "data/bin_char.data", "w");
  fputc( 'F', fp);
  fputc( 'L', fp);
  fputc( 'O', fp);
  fputc( 'A', fp);
  fputc( 'T', fp);
  fclose(fp);
  fp = fopen( "data/bin_str.data", "w");
  fwrite( header, sizeof(header[0]), sizeof(header)/sizeof(header[0]), fp);
  fclose(fp);

  

  return 0;
}
