// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct LOOKUP_ROW {
    int target_key;
    int owner_key;
    void *result;
};
struct LOOKUP_STATE {
    unsigned char reserved00[0xD8];
    int count;
};
extern unsigned char D_00475480[];
void func_001C7DC8(void *);
void *func_0017E1B8(void *, int, int, void *);

void func_001FEA78(void *receiver)
{
    struct LOOKUP_STATE *state = receiver;
    int i = 0;
    func_001C7DC8(receiver);
    for (; i < state->count; ++i) {
        struct LOOKUP_ROW *row = (struct LOOKUP_ROW *)
            ((unsigned char *)receiver + 0xDC) + i;
        void *owner = func_0017E1B8(D_00475480, 5, row->owner_key, 0);
        void *result = func_0017E1B8(D_00475480, owner ? 4 : 5,
                                   row->target_key, owner);
        if (result)
            row->result = result;
    }
}
