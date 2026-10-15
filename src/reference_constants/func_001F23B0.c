// Reference algorithm: src/hand/func_00147220.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
extern char D_00346F70[]; void func_0023C580(void *); void func_001C8970(void *,int,void *,void *);  void func_001F23B0(char *p) { func_0023C580(p); func_001C8970(p,1,D_00346F70,0); func_0023AAE8(*(void **)(p+0x1A0),p,-1,0,(void **)(p+0x1A4)); }
