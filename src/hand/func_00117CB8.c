// Allocate through the real global heap slot and return its allocation pointer.
// Original A0 heap receiver and A2 allocation kind are unused by this method.
typedef struct ALLOCREQ { int cb; int cbAlign; } ALLOCREQ;
void *func_001D2470(ALLOCREQ *request);

void *func_00117CB8(void *heap, int byteCount, int allocationKind)
{
    ALLOCREQ request;
    request.cb = byteCount;
    request.cbAlign = 16;
    return func_001D2470(&request);
}
