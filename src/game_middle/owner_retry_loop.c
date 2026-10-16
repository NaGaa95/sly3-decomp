// SLY3_CFLAGS: -Os -G0
struct RetryOwner { unsigned char opaque0000[0x113C]; void *animation113C; unsigned char opaque1140[0x1C64 - 0x1140]; void *pending1C64; };
int func_00138AC8(void *animation);
void func_001E4900(void *owner, int mode);
void func_001E49B8(void *receiver)
{
    struct RetryOwner *owner = (struct RetryOwner *)receiver;
    void *snapshot;
    do {
        snapshot = owner->pending1C64;
        if (snapshot) {
            if (!owner->animation113C || func_00138AC8(owner->animation113C))
                func_001E4900(receiver, 0);
        }
    } while (owner->pending1C64 != snapshot);
}
