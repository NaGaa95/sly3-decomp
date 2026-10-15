// SLY3_CFLAGS: -O2 -G0
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_ASFIX: sdk-gp64
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
typedef int saddr __attribute__((mode(pointer)));
typedef int sword __attribute__((mode(SI)));
typedef unsigned int uword __attribute__((mode(SI)));
struct dwarf_fde {uword length; sword CIE_delta; void *pc_begin; uaddr pc_range;}
 __attribute__((packed, aligned(__alignof__(void *))));
typedef struct dwarf_fde fde;
struct object {void *pc_begin,*pc_end; fde *fde_begin; fde **fde_array;
 size_t count; struct object *next;};
extern struct object *D_004D0BF8;
extern void func_0029E390(struct object *);
#define init_object_mutex_once()
#include "gthr-single.h"
/* The single-thread gthr functions do not access their mutex argument. */
extern __gthread_mutex_t object_mutex;
fde *
func_0029E4D0 (void *pc)
{
  struct object *ob;
  size_t lo, hi;

  init_object_mutex_once ();
  __gthread_mutex_lock (&object_mutex);

  for (ob = D_004D0BF8; ob; ob = ob->next)
    {
      if (ob->pc_begin == 0)
	func_0029E390 (ob);
      if (pc >= ob->pc_begin && pc < ob->pc_end)
	break;
    }

  __gthread_mutex_unlock (&object_mutex);

  if (ob == 0)
    return 0;

  /* Standard binary search algorithm.  */
  for (lo = 0, hi = ob->count; lo < hi; )
    {
      size_t i = (lo + hi) / 2;
      fde *f = ob->fde_array[i];

      if (pc < f->pc_begin)
	hi = i;
      else if (pc >= f->pc_begin + f->pc_range)
	lo = i + 1;
      else
	return f;
    }

  return 0;
}
