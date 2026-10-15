// SLY3_CFLAGS: -O2 -G0
/*
FUNCTION
	<<tolower>>---translate characters to lower case

INDEX
	tolower
INDEX
	_tolower

ANSI_SYNOPSIS
	#include <ctype.h>
	int tolower(int <[c]>);
	int _tolower(int <[c]>);

TRAD_SYNOPSIS
	#include <ctype.h>
	int tolower(<[c]>);
	int _tolower(<[c]>);


DESCRIPTION
<<tolower>> is a macro which converts upper-case characters to lower
case, leaving all other characters unchanged.  It is only defined when
<[c]> is an integer in the range <<EOF>> to <<255>>.

You can use a compiled subroutine instead of the macro definition by
undefining this macro using `<<#undef tolower>>'.

<<_tolower>> performs the same conversion as <<tolower>>, but should
only be used when <[c]> is known to be an uppercase character (<<A>>--<<Z>>).

RETURNS
<<tolower>> returns the lower-case equivalent of <[c]> when it is a
character between <<A>> and <<Z>>, and <[c]> otherwise.

<<_tolower>> returns the lower-case equivalent of <[c]> when it is a
character between <<A>> and <<Z>>.  If <[c]> is not one of these
characters, the behaviour of <<_tolower>> is undefined.

PORTABILITY
<<tolower>> is ANSI C.  <<_tolower>> is not recommended for portable
programs.

No supporting OS subroutines are required.
*/ 

#define _DEFUN(name,args,declarations) name(declarations)
extern const char D_0032A690[];
#define isupper(c) ((D_0032A690+1)[(unsigned)(c)] & 01)

#undef tolower
int
_DEFUN(func_00293238,(c),int c)
{
	return isupper(c) ? (c) - 'A' + 'a' : c;
}
