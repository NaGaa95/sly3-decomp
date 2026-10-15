// SLY3_CFLAGS: -O2 -G0
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
/* Subroutines needed for unwinding stack frames for exception handling.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1997, 1998, 2000 Free Software Foundation, Inc.
   Contributed by Jason Merrill <jason@cygnus.com>.

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

typedef unsigned int size_t;
typedef unsigned int uaddr __attribute__((mode(pointer)));
typedef int sword __attribute__((mode(SI)));
typedef unsigned int uword __attribute__((mode(SI)));
struct dwarf_fde {uword length; sword CIE_delta; void *pc_begin; uaddr pc_range;}
 __attribute__((packed, aligned(__alignof__(void *))));
typedef struct dwarf_fde fde;
/* Count only genuine FDEs with a linked, nonzero code range.  The
 * original loop retains the current length across the body and copies the
 * next length at the subsequent-iteration join. */
size_t func_0029E2C0(fde *this_fde)
{
    uword length = this_fde->length;
    uword next;
    size_t count = 0;

    if (length != 0)
    {
        goto check;
        do
        {
            length = next;
check:
            if (this_fde->CIE_delta != 0 && this_fde->pc_begin != 0)
                ++count;
            this_fde = (fde *)((char *)this_fde + length + sizeof(length));
            next = this_fde->length;
        } while (next != 0);
    }
    return count;
}
