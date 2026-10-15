// SLY3_CFLAGS: -O2 -G0
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_ASFIX: sdk-gp64
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

extern int func_0029EE58(const char*,const char*);
void *
func_0029CF88 (void *catch_type, void *throw_type, void *obj)
{
#if 0
 printf ("func_0029CF88 (): catch_type = %s, throw_type = %s\n",
	 catch_type, throw_type);
#endif
 if (func_0029EE58 ((const char *)catch_type, (const char *)throw_type) == 0)
   return obj;
 return 0;
}
