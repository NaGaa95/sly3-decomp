// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Preserve three 8-byte fields across func_0022D740 with a scoped save object.
struct Pair { int a, b; };
struct Block { int head; Pair first; Pair second; };
struct Self { unsigned char pad[0x1A8]; Block block; unsigned char pad1BC[0x1C4 - 0x1BC]; Pair extra; };
extern "C" void func_0022D740(Self *self, int a);
struct BlockSave {
    Block *block; Pair first; Pair second;
    BlockSave(Block *p) { block = p; first = p->first; second = block->second; }
    ~BlockSave() { block->first = first; block->second = second; }
};
extern "C" void func_001A0B00(Self *self, int a)
{
    BlockSave save(&self->block);
    Pair extra = self->extra;
    func_0022D740(self, a);
    self->extra = extra;
}
