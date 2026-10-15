// GCC fp-bit float unpacker, Sly2 source reference; observed exponent-zero flush retained.
// SLY3_CFLAGS: -O2 -G0
/* This is a software floating point library which can be used instead of
   the floating point routines in libgcc1.c for targets without hardware
   floating point. 
 Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

typedef unsigned int fractype;
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union { fractype ll; } fraction;
} fp_number_type;
typedef union {
    float value;
    fractype value_raw;
    struct { fractype fraction:23; unsigned int exp:8; unsigned int sign:1; } bits;
} FLO_union_type;

void func_0029CD88(FLO_union_type *src, fp_number_type *dst)
{
    fractype fraction;
    int exp;
    int sign;

    sign = src->bits.sign;
    exp = src->bits.exp;
    fraction = src->bits.fraction;

    dst->sign = sign;
    if (exp == 0)
    {
        if (fraction == 0 || 1)
        {
            dst->class = CLASS_ZERO;
        }
    }
    else if (exp == 255)
    {
        if (fraction == 0)
        {
            dst->class = CLASS_INFINITY;
        }
        else
        {
            if (fraction & 0x100000)
                dst->class = CLASS_QNAN;
            else
                dst->class = CLASS_SNAN;
            dst->fraction.ll = fraction;
        }
    }
    else
    {
        dst->normal_exp = exp - 127;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << 7) | 0x40000000;
    }
}
