/*
** gdt.c			: WISDOM
** Purpose  		: Sets up the Global descriptor tables
** Website 			: wisdom.sourceforge.net
** Copyright (C) 2003 	  Anita Shelton ( anitashelton@gmx.net ) 
**			    	  R Karthick    ( rkarthick@gmx.net )
** Source code references from jijos-0.3.3
*/

#include "gdt.h"
#include "types.h"

/* The NULL descriptor */
DESCRIPTOR *GDT = (DESCRIPTOR *)0;



/***
* 3-8 in intel
****/

/***
*
* Name of the function	: setupGDT
* Purpose 			: To set up the global descriptor table.
*
***/


void setupGDT( void )
{
	DWORD GDTR[2];

	// printf( "\nSetting up GDT    ......................" );

	setupDescriptor( &GDT[1],0,FOURGB,8,0,1,1 );  /* Kernel Code - 0x08 */
	setupDescriptor( &GDT[2],0,FOURGB,2,0,1,1 );  /* Kernel Data - 0x10 */
	setupDescriptor( &GDT[3],0,FOURGB,8,3,1,1 );  /* User Code  - 0x1B */
	setupDescriptor( &GDT[4],0,FOURGB,2,3,1,1 );  /* User Data  - 0x23 */

	GDTR[0] = ((GDT_SIZE * sizeof(DESCRIPTOR)) - 1)  << 16;
	GDTR[1] = (DWORD)GDT;

	__asm__ __volatile__("lgdt (%0)" : : "r" (((BYTE *)GDTR) + 2));

	flushiqandsetsegmentreg();
	// printf( " [DONE] " );


}

/***
*
* Name of the function	: flushiqandsetsegmentreg
* Purpose 			: Flushes the instruction queue and sets the segment selectors 
*				  with new segment selectors.
*
***/


void flushiqandsetsegmentreg(void)
{

	  __asm__ __volatile__("ljmp $8, $__flush\n"
          "__flush:");

	  __asm__ __volatile__("movl $0x10, %eax\n"
          "movw %ax, %ss\n"
          "movl $0x23, %eax\n"
          "movw %ax, %ds\n"
          "movw %ax, %es\n"
          "movw %ax, %fs\n"
          "movw %ax, %gs");

}

/***
*
* Name of the function	: setupDescriptor
* Formal Parameters 	: *d,baseaddress,segmentlimit,type,dpl,systemflag,db
* @d				: pointer to the particular descriptor
* @baseaddress		: The base address of the segment the descriptor points 
*				   to.
* @segmentlimit		: The segment limit or the size to which it extends.
* @type			: Indicates the segment or gate type and specifies the 
*				  kinds of access that can be made to the segment and 
*				  the direction of  growth.
* @dpl			: Descriptor privilege level.
* @systemflag		: Specifies the segment sector is for system segmen or 
*				  a code or data segment
* @db  			: Default Operation size/default stack pointer size
* Purpose 			: Sets up the individual descriptor and loads it with 
*				  the segment specific information. 
*
***/

void setupDescriptor( DESCRIPTOR *d, DWORD baseaddress, DWORD segmentlimit, BYTE type, BYTE dpl, BYTE systemflag, BYTE db)
{
	makezero( d );
	segmentlimit		= segmentlimit >> 12;
	d->granularity 		= 1;
	d->baseaddress0_15	= baseaddress;
	d->baseaddress16_23	= baseaddress >> 16;	
	d->baseaddress24_31	= baseaddress >> 24;	
	d->segmentlimit0_15	= segmentlimit;
	d->segmentlimit16_19	= segmentlimit >> 16;
	d->type			= type;
	d->dpl			= dpl;
	d->systemflag		= systemflag;
	d->db				= db;
	d->present			= 1;
	d->avl			= 0;
	d->zero			= 0;
	
}


/***
*
* Name of the function	: makezero
* Formal Parameters 	: *d
* @d 	 			: the reference to that particular descriptor
* Purpose 			: nullify all the contents of the descriptor before 
*				  writing it so that it may not contain any junk data
*
***/


void makezero( DESCRIPTOR *d )
{
	d->granularity 		= 0;
	d->baseaddress0_15	= 0;
	d->baseaddress16_23	= 0;	
	d->baseaddress24_31	= 0;
	d->segmentlimit0_15	= 0;
	d->segmentlimit16_19	= 0;
	d->type			= 0;
	d->dpl			= 0;
	d->systemflag		= 0;
	d->db				= 0;
	d->present			= 0;
	d->avl			= 0;
	d->zero			= 0;
}

