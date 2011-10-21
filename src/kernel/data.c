#include "data.h"
#include "monitor.h"

// itoa related functions here
// http://www.koders.com/c/fid5F9B1CF12E947E5030A132D309A367C5CCB671CE.aspx

void
itoa(char (* dest)[11] , int value)
{
  char tmp[33];
  char *tp = tmp;
  int i;
  unsigned v;
  int sign;
  char *sp;
  int radix = 10;

  sign = (value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = &(*dest)[0];

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
}

void
uitoa(char (* dest)[11] ,uint32 value)
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v = value;
  char *sp;
 	int radix = 10;

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = &(*dest)[0];

 
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
}

void
ltoa(char (* dest)[20] ,long value)
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char *sp;
	int radix = 10;

  sign = (value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned long)value;
  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

	sp = &(*dest)[0];

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
}

void
ultoa(char (* dest)[20] ,unsigned long value)
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v = value;
  char *sp;
 	int radix = 10;

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = &(*dest)[0];

 
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
}

void ustoa( char (* dest)[6] , uint16 src ){
	const int ascii_offset = 48;
	uint32 div = 10000;
	uint32 quotient = 0;
	int digit = 0;
	while( div > 0 ){
		quotient = src / div;
		src -= ( quotient * div );
		(*dest)[digit] = (char) ((quotient + ascii_offset) & 0xFF) ;
		digit++;		
		div /= 10;
	}
	// add null terminator
	(*dest)[5] = 0;
}

//void uitob( char (* dest)[33] , uint32 src ){
		


//}

void uitoh( char (* dest)[11] , uint32 src ){
		
	int digit = 9;
	int half_byte = 0;

	// initialize hex string to ascii zero
	(*dest)[0] = '0';
	(*dest)[1] = 'x';
	(*dest)[10] = '\0';
	for( digit = 2 ; digit<10 ; digit++ ){
		(*dest)[digit] = '0';
	}
	digit--;

	while( src > 0 ){
		half_byte = src & 0xF;
		if( half_byte >= 0xA )
			(*dest)[digit] = (char) ((half_byte + 55) & 0xFF);
		else
			(*dest)[digit] = (char) ((half_byte + 48) & 0xFF);
		src = src >> 4;
		digit--;
	}

}

void hbtoa( BYTE_HEX * dest , uint8 src ){
	if( ( src >> 4 ) >= 0xA )
		dest->hi = ( src >> 4 ) + 55;
	else
		dest->hi = ( src >> 4 ) + 48;
	if( ( src & 0xF ) >= 0xA )
		dest->lo = ( src & 0xF ) + 55;
	else
		dest->lo = ( src & 0xF ) + 48;
}

