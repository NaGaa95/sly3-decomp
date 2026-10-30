// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self { unsigned char pad[0x120]; float g120; };
/* .data value at 0x345700 (250.0f), not in symbol_addrs; placed by its bytes. */
static float D_00345700 = 250.0f;
void func_001A21B0(struct Self *self, float *pg)
{
    *pg = *pg - (self->g120 - (D_00345700 - 150.0f));
}
