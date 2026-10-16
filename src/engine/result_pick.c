// SLY3_CFLAGS: -Os -G0
struct EnginePickOwner { unsigned char prefix[0x1108]; void *lookup; unsigned char gap[4]; int fallback; };
int func_00173428(void *lookup);
int func_00153620(struct EnginePickOwner *owner)
{
    int ok=0;
    if(owner->lookup) ok=func_00173428(owner->lookup)!=0;
    if(ok) return 0x80;
    return owner->fallback;
}
