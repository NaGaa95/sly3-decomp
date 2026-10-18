// SLY3_CFLAGS: -Os -G0
struct TokenModeOwner {
    char prefix[0x130];
    int mode;
    float changed;
    int unused138;
    void *token;
    int unused140;
    int index;
};
struct TokenModeRow { int key; int value; };
extern struct TokenModeRow D_003210E0[];
struct TokenModeClock { float now, step; };
extern struct TokenModeClock D_0036BB98;
void func_00239CE8(void *token, int value);
int func_0011E8F0(int lower, int upper);

void func_00170F60(struct TokenModeOwner *owner, int mode)
{
    if(owner->mode == mode)
        return;
    owner->mode = mode;
    owner->changed = D_0036BB98.now;
    switch(mode) {
    case 0:
        owner->index = (owner->index + 9) % 10;
        func_00239CE8(owner->token, D_003210E0[owner->index].value);
        break;
    case 1:
        owner->index = (owner->index + 1) % 10;
        func_00239CE8(owner->token, D_003210E0[owner->index].value);
        break;
    case 2:
        owner->index = func_0011E8F0(0, 9);
        func_00239CE8(owner->token, D_003210E0[owner->index].value);
        break;
    }
}
