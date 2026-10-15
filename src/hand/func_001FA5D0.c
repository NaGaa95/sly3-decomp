// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct E { char pad[0x18]; int *ap; char pad2[0x50]; };
extern struct E *D_00479AB0;
int func_001FA5C0(int handle);
int func_001FA5B8(int handle);
int func_001FA5D0(int handle)
{
    struct E *pe;
    if (func_001FA5C0(handle) == -1) return -1;
    pe = &D_00479AB0[func_001FA5B8(handle)];
    return pe->ap[func_001FA5C0(handle)];
}
