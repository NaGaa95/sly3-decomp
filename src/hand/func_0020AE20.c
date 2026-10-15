// Store all three actual scalar inputs and call the adjusted virtual method with explicit selector32 and four null inputs. Its nominal indirect API is provisional; all six observed GP arguments are explicit.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *,int,void *,void *,void *,void *);};
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x480]; int first; int second; int third; };
void func_0020AE20(struct S *p,int first,int second,int third){p->first=first;p->second=second;p->third=third;p->vtable[3].method((char *)p+p->vtable[3].delta,32,0,0,0,0);}
