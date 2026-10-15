// GCC 2.95.3 libgcc2.c, L_floatdisf; original algorithm and notice retained.
// SLY3_CFLAGS: -O2 -G0
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_ASFIX: sdk-softdf
/* More subroutines needed by GCC output code on some machines.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));
#define BITS_PER_UNIT 8
#define WORD_SIZE (sizeof (SItype) * BITS_PER_UNIT)
#define HIGH_HALFWORD_COEFF (((UDItype) 1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype) 1) << WORD_SIZE)
#define DI_SIZE (sizeof (DItype) * BITS_PER_UNIT)

/* Define codes for all the float formats that we know of.  Note
   that this is copied from real.h.  */
   
#define UNKNOWN_FLOAT_FORMAT 0
#define IEEE_FLOAT_FORMAT 1
#define VAX_FLOAT_FORMAT 2
#define IBM_FLOAT_FORMAT 3

/* Default to IEEE float if not specified.  Nearly all machines use it.  */
#ifndef HOST_FLOAT_FORMAT
#define	HOST_FLOAT_FORMAT	IEEE_FLOAT_FORMAT
#endif

#if HOST_FLOAT_FORMAT == IEEE_FLOAT_FORMAT
#define DF_SIZE 53
#define SF_SIZE 24
#endif

#if HOST_FLOAT_FORMAT == IBM_FLOAT_FORMAT
#define DF_SIZE 56
#define SF_SIZE 24
#endif

#if HOST_FLOAT_FORMAT == VAX_FLOAT_FORMAT
#define DF_SIZE 56
#define SF_SIZE 24
#endif

SFtype
func_0029ACF8 (DItype u)
{
  /* Do the calculation in DFmode
     so that we don't lose any of the precision of the high word
     while multiplying it.  */
  DFtype f;

  /* Protect against double-rounding error.
     Represent any low-order bits, that might be truncated in DFmode,
     by a bit that won't be lost.  The bit can go in anywhere below the
     rounding position of the SFmode.  A fixed mask and bit position
     handles all usual configurations.  It doesn't handle the case
     of 128-bit DImode, however.  */
  if (DF_SIZE < DI_SIZE
      && DF_SIZE > (DI_SIZE - DF_SIZE + SF_SIZE))
    {
#define REP_BIT ((USItype) 1 << (DI_SIZE - DF_SIZE))
      if (! (- ((DItype) 1 << DF_SIZE) < u
	     && u < ((DItype) 1 << DF_SIZE)))
	{
	  if ((USItype) u & (REP_BIT - 1))
	    u |= REP_BIT;
	}
    }
  f = (SItype) (u >> WORD_SIZE);
  f *= HIGH_HALFWORD_COEFF;
  f *= HIGH_HALFWORD_COEFF;
  f += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return (SFtype) f;
}
