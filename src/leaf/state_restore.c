// Runtime snapshot fields, not initialized data or preserved original bytes.
// SLY3_CFLAGS: -Os -G0
struct RestoreProgress {
    unsigned char bytes[0x6808];
};
struct RestoreSettings {
    unsigned char bytes[0x1488];
};
struct RestoreInput {
    unsigned char reserved0[0x34];
    int state;
    struct RestoreProgress progress;
    struct RestoreSettings settings;
    int first_id;
    int second_id;
    int third_id;
};
struct RestoreContext {
    unsigned char reserved0[0x10];
    struct RestoreSettings settings;
    int first_id;
    int second_id;
    int third_id;
};
extern unsigned int D_004797C8;
extern unsigned char D_0036C700[], D_0036C710[], D_00468D30[], D_00375290[];
void func_001CFDE8(void *, int);
typedef char RestoreProgressWidth[(sizeof(struct RestoreProgress) == 0x6808) ? 1 : -1];
typedef char RestoreSettingsWidth[(sizeof(struct RestoreSettings) == 0x1488) ? 1 : -1];
typedef char RestoreInputWidth[(sizeof(struct RestoreInput) == 0x7CD4) ? 1 : -1];

void func_002837A0(struct RestoreInput *input)
{
    if (D_004797C8 & 0x40) {
        struct RestoreContext *context = (struct RestoreContext *)D_0036C700;
        context->first_id = input->first_id;
        context->second_id = input->second_id;
        context->third_id = input->third_id;
        input->state = -1;
        input->first_id = -1;
        input->second_id = -1;
        input->third_id = -1;
        *(struct RestoreProgress *)D_00468D30 = input->progress;
        func_001CFDE8(D_00375290, 0);
        *(struct RestoreSettings *)D_0036C710 = input->settings;
    }
}
