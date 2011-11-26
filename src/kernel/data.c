#include "data.h"

/*
* SIGNED/UNSIGNED DATA TYPES - max # chars needed for string representation (incl null term)
*   unsigned data types needs one less character (no char to represent sign character)
* byte - 5 
* short - 7
* int - 12
* long - 12
* int 64 bit - 21
*
* UNSIGNED DATA TYPES ONLY
* char - 2 (unsigned only)
*
* SIGNED DATA TYPES ONLY
* float - 11
* double - 21
*
*/

// ****************************************************************
//
//				SIGNED DATA CONVERSION FUNCTIONS
//
// ****************************************************************

char *
btoa(char * dest , BYTE value , BOOL is_unsigned )
{
  char tmp[5];
  char *tp = tmp;
  int i;
  UBYTE v;
  BOOL sign = FALSE;
  char *sp;
  int radix = 10;
	int num_digits = 0;

	//
	if( !is_unsigned ){
		sign = (value < 0);
		if (sign)
		  v = -value;
		else
		  v = (UBYTE) value;	
	}
	else{
		v = (UBYTE) value;	
	}

	// special case
	if( v == 0 ){
		*tp++ = '0';
		num_digits++;
	}

  while (v)
  {
    i = v % radix;
    v = v / radix;
    *tp++ = i+'0';
		num_digits++;
  }

  sp = &dest[0];

  if (sign)
    *sp++ = '-';
  while ( num_digits-- > 0 )
    *sp++ = *--tp;
  *sp = 0;
	
	return sp;
}

char *
shtoa(char * dest , short value , BOOL is_unsigned )
{
  char tmp[7];
  char *tp = tmp;
  int i;
  uint16 v;
  BOOL sign = FALSE;
  char *sp;
  int radix = 10;
	int num_digits = 0;

	//
	if( !is_unsigned ){
		sign = (value < 0);
		if (sign)
		  v = -value;
		else
		  v = (uint16) value;	
	}
	else{
		v = (uint16) value;	
	}

	// special case
	if( v == 0 ){
		*tp++ = '0';
		num_digits++;
	}

  while (v)
  {
    i = v % radix;
    v = v / radix;
    *tp++ = i+'0';
		num_digits++;
  }

  sp = &dest[0];

  if (sign)
    *sp++ = '-';
  while ( num_digits-- > 0 )
    *sp++ = *--tp;
  *sp = 0;

	return sp;
}

char *
itoa(char * dest , int value , BOOL is_unsigned )
{
  char tmp[12];
  char *tp = tmp;
  int i;
  unsigned int v;
  BOOL sign = FALSE;
  char *sp;
  int radix = 10;
	int num_digits = 0;

	//
	if( !is_unsigned ){
		sign = (value < 0);
		if (sign)
		  v = -value;
		else
		  v = (uint32) value;	
	}
	else{
		v = (uint32) value;	
	}

	// special case
	if( v == 0 ){
		*tp++ = '0';
		num_digits++;
	}

  while (v)
  {
    i = v % radix;
    v = v / radix;
    *tp++ = i+'0';
		num_digits++;
  }

  sp = &dest[0];

  if (sign)
    *sp++ = '-';
  while ( num_digits-- > 0 )
    *sp++ = *--tp;
  *sp = 0;

	return sp;
}

char *
ltoa(char * dest , long value , BOOL is_unsigned )
{
  char tmp[12];
  char *tp = tmp;
  int i;
  unsigned long v;
  BOOL sign = FALSE;
  char *sp;
  int radix = 10;
	int num_digits = 0;

	//
	if( !is_unsigned ){
		sign = (value < 0);
		if (sign)
		  v = -value;
		else
		  v = (unsigned long) value;	
	}
	else{
		v = (unsigned long) value;	
	}

	// special case
	if( v == 0 ){
		*tp++ = '0';
		num_digits++;
	}

  while (v)
  {
    i = v % radix;
    v = v / radix;
    *tp++ = i+'0';
		num_digits++;
  }

  sp = &dest[0];

  if (sign)
    *sp++ = '-';
  while ( num_digits-- > 0 )
    *sp++ = *--tp;
  *sp = 0;

	return sp;
}

// TODO: implement me
char *
ftoa( char * dest , float value)
{
  dest[0] = '\0';
	value = 0.0;

	return NULL;
}

// TODO: implement me
char *
dtoa( char * dest , double value)
{
  dest[0] = '\0';
	value = 0.0;

	return NULL;
}

// TODO:
char *
i64toa( char * dest , int64 value , BOOL is_unsigned )
{
	dest[0] = '\0';
	value = 0;
	is_unsigned = FALSE;

	return NULL;
}

// ****************************************************************
//
//				HEX DATA CONVERSION FUNCTIONS
//
// ****************************************************************

char * uitoh( char * dest , uint32 src ){
		
	int digit = 9;
	int half_byte = 0;

	// initialize hex string to ascii zero
	(dest)[0] = '0';
	(dest)[1] = 'x';
	(dest)[10] = '\0';
	for( digit = 2 ; digit<10 ; digit++ ){
		(dest)[digit] = '0';
	}
	digit--;

	while( src > 0 ){
		half_byte = src & 0xF;
		if( half_byte >= 0xA )
			(dest)[digit] = (char) ((half_byte + 55) & 0xFF);
		else
			(dest)[digit] = (char) ((half_byte + 48) & 0xFF);
		src = src >> 4;
		digit--;
	}

	return dest + 10;
}

void hbtoa( BYTE_HEX * dest , UBYTE src ){
	if( ( src >> 4 ) >= 0xA )
		dest->hi = ( src >> 4 ) + 55;
	else
		dest->hi = ( src >> 4 ) + 48;
	if( ( src & 0xF ) >= 0xA )
		dest->lo = ( src & 0xF ) + 55;
	else
		dest->lo = ( src & 0xF ) + 48;
}

