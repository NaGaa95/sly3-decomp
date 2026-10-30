// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct Self { unsigned char pad[0xC]; struct VTE *pvt; };
void func_0019BC38(struct Self *self)
{
    self->pvt[9].pfn((char *)self + self->pvt[9].delta);
}
