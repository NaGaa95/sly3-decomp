// Reference: Sly 2 src/lib/InitTLB.c; target Sly 3 0x00299FE8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int GetMemorySize(void);
void InitTLB32MB(void);
void _InitTLB(void);
void InitTLB(void)
{
    if (GetMemorySize() == 0x2000000) InitTLB32MB();
    else _InitTLB();
}
