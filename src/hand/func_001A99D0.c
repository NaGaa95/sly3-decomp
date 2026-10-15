// Request initialization: real owner pointer and two cleared 32-bit state words.
#include "activation_selector_api.h"
struct RequestPrefix { void *owner; int state; union { float seconds; unsigned int bits; } elapsed; };
void func_001A99D0(void *record, void *owner)
{
    struct RequestPrefix *request = record;
    request->elapsed.bits = 0;
    request->state = 0;
    request->owner = owner;
}
