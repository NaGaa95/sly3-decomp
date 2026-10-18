// SLY3_CFLAGS: -Os -G0
struct FocusIds {
    unsigned char prefix[0x1498];
    int firstId, secondId, thirdId, fourthId;
};
struct FocusGame {
    unsigned char prefix[0x4348];
    unsigned int flags4348;
};
struct FocusRecord {
    unsigned char prefix[0x54];
    void *set54;
};
extern struct FocusGame D_00475480;
void *func_0017E1B8(void *game, int kind, int id, void *owner);
void func_0018A0D0(void *set);
void func_0018AAE0(void *game, void *set);
void func_00184AA0(struct FocusIds *self)
{
    void *set = func_0017E1B8(&D_00475480, 0x105, self->thirdId, 0);
    if(D_00475480.flags4348 & 4) {
        self->thirdId = -1;
        if(!set) {
            struct FocusRecord *record = func_0017E1B8(&D_00475480, 0x105, self->firstId, 0);
            if(record) set = record->set54;
        }
        if(set) func_0018A0D0(set);
        else func_0018AAE0(&D_00475480, 0);
    } else if(!set) func_0018AAE0(&D_00475480, 0);
}
