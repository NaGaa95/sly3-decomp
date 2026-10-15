// Reference algorithm: src/hand/func_00210990.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[8]; };
extern struct E D_00321240[];
struct E *func_00175240(int i)
{
    if (i == -1)
        return 0;
    { struct E *entry = D_00321240 + i; return entry; }
}
