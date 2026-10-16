// SLY3_CFLAGS: -Os -G0
struct RefreshRequest {
    void *object;
    unsigned char unaccessed04[4];
    int mode;
    unsigned char unaccessed0C[8];
};
struct RefreshOwnerPrefix {
    unsigned char unaccessed00[0xD8];
    int count;
    struct RefreshRequest requests[32];
};
typedef char RefreshRequestSize[(sizeof(struct RefreshRequest) == 20) ? 1 : -1];
int func_00170580(void *owner, void *object, int previousMode);
void func_00170410(void *owner, struct RefreshRequest *request, int mode);

void func_0016FCF8(void *receiver)
{
    struct RefreshOwnerPrefix *owner = receiver;
    int i;
    for (i = 0; i < owner->count; ++i) {
        struct RefreshRequest *request = owner->requests + i;
        int mode = func_00170580(owner, request->object, request->mode);
        func_00170410(owner, request, mode);
    }
}
