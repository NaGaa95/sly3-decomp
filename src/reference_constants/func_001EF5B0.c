// Original USA entry 0x1ef5b0; ordinary C reconstruction.
// Receiver A0 only. Signed refcount288 is decremented; nonpositive count calls11B028(registration47A418,receiver), then11E1F0(pool47A400,receiver). Both original two-pointer inputs are explicit. The verified24-byte separation describes original list/pool storage rather than an invented constant object.
// SLY3_CFLAGS: -Os -G0
extern char D_0047A400[];
void func_0011B028(void *,void *);
void func_0011E1F0(void *,void *);
void func_001EF5B0(char *p)  {
    if(--*(int *)(p+0x288)<=0) {
        char *registration=D_0047A400+24;
        func_0011B028(registration,p);
        func_0011E1F0(registration-24,p);
    }
}
