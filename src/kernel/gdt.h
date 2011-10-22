/*
** gdt.h			: WISDOM
** Purpose  		: 
** Overview 		:
** Website 			: wisdom.sourceforge.net
** Copyright (C) 2003 	  Anita Shelton ( anitashelton@gmx.net ) 
**			    	  R Karthick    ( rkarthick@gmx.net )
*/

#ifndef _GDT_H
#define _GDT_H

#include "types.h"

#define GDT_SIZE 	8192

#define 	KERNEL_CS		0x08
#define		KERNEL_DS		0x10
#define		USER_CS		  0x18
#define		USER_DS		  0x20

#define FOURGB 	0xFFFFFFFF


struct Descriptor{
	WORD segmentlimit0_15;
	WORD baseaddress0_15;
	BYTE baseaddress16_23;
	BYTE type : 4;
	BYTE systemflag : 1;
	BYTE dpl : 2;
	BYTE present : 1;
	BYTE segmentlimit16_19 : 4;
	BYTE avl : 1;
	BYTE zero : 1;
	BYTE db : 1;
	BYTE granularity : 1;
	BYTE baseaddress24_31;
};

typedef struct Descriptor DESCRIPTOR;
void makezero( DESCRIPTOR *d );

DESCRIPTOR *GDT;
void setupGDT(void);
//void lgdt( struct gdtr* );
void flushiqandsetsegmentreg();

void setupDescriptor( DESCRIPTOR *d, DWORD baseaddress, DWORD segmentlimit, BYTE type, BYTE dpl, BYTE systemflag, BYTE db);

#endif

