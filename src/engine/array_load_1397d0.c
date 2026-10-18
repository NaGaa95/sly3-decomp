// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct ArrayRequest { int bytes, alignment; };
struct ArrayOwner { unsigned char prefix[0xF4]; int count; void *array; };
CRef *func_0024B330(CRef *output, CRef *input, int type, int format, int *count, void **values);
void *func_001D24D0(struct ArrayRequest *request, void *source);
static inline struct ArrayRequest *allocation_request(struct ArrayRequest *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}
void func_001397D0(struct ArrayOwner *self, CRef *input)
{
    void *buffer[16];
    CRef status;
    struct ArrayRequest request;
    int count;
    func_0024B330(&status, input, 0x1040, 0x10, &count, buffer);
    func_0012BC20(&status);
    self->count = count;
    self->array = func_001D24D0(allocation_request(&request, count * 4, 0x10), buffer);
}
