// SLY3_CFLAGS: -Os -G0
struct MovieBatchRecord { unsigned char bytes[0x40]; };
struct MovieBatch {
    int count;
    struct MovieBatchRecord records[4];
    int status;
    int repeat;
};
extern unsigned char D_0036DBE0[];
int func_001D23E0(int unused_request);
int func_001DAA00(void *unused_record);
void func_00196228(void *screen, int mode);
void func_001DBE80(void *state, void *record);

int func_001DBDB8(struct MovieBatch *state)
{
    int index;
    if (state->count <= 0)
        return 0;
    if ((unsigned int)func_001D23E0(1) <= 0x41FC3F) {
        state->count = 0;
        return 0;
    }
    func_00196228(D_0036DBE0, 0);
    for (index = 0; index < state->count; ++index) {
        struct MovieBatchRecord *record = &state->records[index];
        state->status = func_001DAA00(record);
        do {
            func_001DBE80(state, record);
        } while (state->repeat);
        state->status = 0;
    }
    state->count = 0;
    return 1;
}
