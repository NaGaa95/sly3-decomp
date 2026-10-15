// Menu update recovered from Sly2func001ACCC8 and full original.
// SLY3_CFLAGS: -Os -G0
// The fixed original323BE8 descriptor is a direct callback: delta0/index-1.
// Its integer result is consumed by the original1CEE48 worker at context+10.
// Match the actual shared reference worker's8-byte direct PMF representation.
// Its second short namedpad contains index-1 in this fixed original descriptor;
// the receiver-only worker reads delta and directpfn and ignores that short.
struct PMF { short delta,pad; int (*pfn)(void *); };
struct S { int x0,x4; struct PMF pmf; int x10; };
struct INPUT_INTERFACE; // Opaque C view of the canonical public C++ interface.
typedef char pmf_size8[(sizeof(struct PMF)==8)?1:-1];
struct MenuRecord { char pad0[0x48];int kind;float changedAt;int pad50;int category; };
struct MenuState { char pad0[0x1C];struct INPUT_INTERFACE *binding;char pad20[0x14];struct MenuRecord *record;char pad38[0x18];int state;int pad54;int selection;int pad5C;int action; };
struct MenuContext { char pad0[8];int mode;char padC[0x13950-12];int word13950;int word13954;int word13958;char pad1395C[0x13970-0x1395C];int operationResult; };
struct Clock { char pad0[0x40];float time; };
extern struct MenuContext D_00375290;
extern struct Clock D_0036BB98;
extern char D_00475480[],D_0046F550[];
extern struct S D_00388BF0;
// Only the zero/nonzero state of this opaque original32-bit word is consumed.
extern unsigned int D_0046FC80;
extern const struct PMF D_00323BE8;
int func_0025AE28(void *context);
int func_001D0D78(struct MenuState *state);
#include "input_query_api.h"
void func_001D1370(struct MenuState *state);
void func_001D1190(struct MenuState *state);
int func_001CEFB8(void *context);
void func_001CEEC0(struct S *context,struct PMF member);
void func_001D0C08(struct MenuState *state,int mode);
void func_001D0C88(struct MenuState *state);
void func_001D0D30(struct MenuState *state,int selection);
void func_0018AB08(int value);
void func_0018AD90(void);
void func_001D3AE8(void *context);
void func_001D0DC8(struct MenuState *s) {
    struct MenuRecord *p=s->record;
    int category, result;
    if(!p)return;
    if(p->kind!=2)return;
    category=p->category;
    if(category!=2)return;
    if(func_0025AE28(D_00475480))return;
    if(D_0036BB98.time-s->record->changedAt<=0.1f)return;
    result=func_001D0D78(s);
    switch(result) {
    case 2:
        if(s->binding && func_001A7A80(s->binding,0x80,0.0f)) {
            func_001D1370(s);return;
        }
        if(s->binding && func_001A7A80(s->binding,0x10,0.0f)) {
            func_001D1190(s);return;
        }

        break;
    case 3:
        if(s->binding && func_001A7A80(s->binding,0x80,0.0f)) {
            func_001D1190(s);return;
        }
        if(s->binding && func_001A7A80(s->binding,0x10,0.0f)) {
            func_001D1370(s);return;
        }

        break;
    case 1:
        if(s->binding && func_001A7A80(s->binding,0x80,0.0f)) {
            func_001D1190(s);return;
        }

        break;
    }
    switch(s->state) {
    case 0x2D:
    case 0x2F:
        if(s->selection==1)return;
        func_001D0C88(s);return;
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x20:
    case 0x23:
    case 0x24:
    case 0x3B:
    case 0x3E:
    case 0x3F:
        if(D_00375290.mode!=6)return;
        func_001D0C88(s);return;
    case 0x1E:
        if(func_001CEFB8(&D_00388BF0))return;
        if(!D_00375290.operationResult) {
            func_001CEEC0(&D_00388BF0,D_00323BE8);
            func_001D0C08(s,0x21);
        } else func_001D0C08(s,0x1F);
        return;
    case 0x21:
        if(func_001CEFB8(&D_00388BF0))return;
        if(!D_00375290.operationResult) {
            if(!D_0046FC80) { func_001D0C88(s); return; }
            if(D_00375290.mode!=6)return;
            func_001D0C88(s);
            func_001D0D30(s,1);
            D_00375290.word13950=D_00375290.word13954;
            func_0018AB08(D_00375290.word13954);
            return;
        }
        func_001D0C08(s,0x22);return;
    case 0x26:
        if(func_001CEFB8(&D_00388BF0))return;
        if(!D_00375290.operationResult) {
            func_001D0C88(s);
            switch(s->action) {
            case 1:func_0018AD90();return;
            case 2:func_001D3AE8(D_0046F550);return;
            }
            return;
        }
        if(s->action==3)func_001D0C08(s,0x30);
        else func_001D0C08(s,0x29);
        return;
    case 0x2E:
        if(func_001CEFB8(&D_00388BF0))return;
        D_00375290.word13958=0;
        if(!D_00375290.operationResult) {func_001D0C88(s);return;}
        func_001D0C08(s,0x29);return;
    }
}
