// SLY3_CFLAGS: -Os -G0
#include "curve_allocation_api.h"

struct S;
struct S *func_002BBC00(struct S *object);
struct S *func_002BBBC8(struct S *object);
struct S *func_002BBC88(struct S *object);
extern int D_0036B238;

struct S *func_0012EF30(int kind, void *context)
{
    switch (kind) {
    case 0:
        D_0036B238 = 20;
        return func_002BBC00(func_0012EF00(8, context));
    case 1:
        D_0036B238 = 19;
        return func_002BBBC8(func_0012EF00(12, context));
    case 2:
        D_0036B238 = 21;
        return func_002BBC88(func_0012EF00(20, context));
    }
    return 0;
}
