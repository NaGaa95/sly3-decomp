// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B330(CRef *, CRef *, int, int, int *, int *);
void func_001C4920(void *, int, const int *, int, const int *);
}

extern "C" void func_001C4A38(void *cursor, CRef *included, CRef *excluded)
{
    int included_values[16];
    CRef included_status;
    int excluded_values[16];
    CRef excluded_status;
    int included_count;
    int excluded_count;

    func_0024B330(&included_status, included, 7, 16,
        &included_count, included_values);
    func_0024B330(&excluded_status, excluded, 7, 16,
        &excluded_count, excluded_values);
    func_001C4920(cursor, included_count, included_values,
        excluded_count, excluded_values);
    func_0012BC20(&excluded_status);
    func_0012BC20(&included_status);
}
