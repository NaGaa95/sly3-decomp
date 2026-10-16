// SLY3_CFLAGS: -Os -G0
struct LoadOnceOwner { char prefix[0xA8]; int loaded; };
void func_00135FB0(void *owner, void *stream, void *context);
void func_00135F48(struct LoadOnceOwner *owner, int unused_word, void *stream, void *context)
{
    if (!owner->loaded) {
        owner->loaded = 1;
        func_00135FB0(owner, stream, (char *)context + 0x50);
    }
}
