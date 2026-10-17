// SLY3_CFLAGS: -Os -G0
#include "output_types.h"
struct AllocRequest { int bytes, alignment; };
void *func_001D25B0(struct AllocRequest *request);
struct Output *func_0025A210(struct Output *output, void *memory, int capacity, int buffer_capacity)
{
    output->memory = memory;
    output->capacity = capacity;
    output->handle = -1;
    output->position = 0;
    output->total = 0;
    output->buffer_count = 0;
    if (buffer_capacity) {
        struct AllocRequest request;
        request.bytes = output->buffer_capacity = buffer_capacity;
        request.alignment = 0x10;
        output->buffer = func_001D25B0(&request);
    } else {
        output->buffer_capacity = 0x400;
        output->buffer = output->inline_buffer;
    }
    return output;
}
