// SLY3_CFLAGS: -Os -G0
typedef int AttachmentRawVector __attribute__((mode(TI)));
typedef struct AttachmentMatrix { AttachmentRawVector rows[4]; } AttachmentMatrix;
typedef struct AttachmentMatrixMethod {
    short adjustment, reserved;
    const AttachmentMatrix *(*get)(void *receiver);
} AttachmentMatrixMethod;
typedef struct AttachmentPosition {
    char prefix[0x20];
    AttachmentRawVector position;
} AttachmentPosition;
typedef struct AttachmentOwner {
    char prefix[0xC];
    AttachmentMatrixMethod *table;
    char unaccessed[0x37C-0x10];
    AttachmentPosition *attachment;
} AttachmentOwner;
typedef struct AttachmentUpdateState {
    char prefix[0x10];
    AttachmentOwner *owner;
    char unaccessed[0x50-0x14];
    int mode;
    int word54;
    float deadline;
} AttachmentUpdateState;
typedef struct AttachmentUpdateClock { float time; } AttachmentUpdateClock;
extern AttachmentUpdateClock D_0036BB98;
void func_001317B0(void *state);
void func_0016D480(void *state, int mode);

void func_0016D540(AttachmentUpdateState *state)
{
    int previous;
    func_001317B0(state);
    do {
        previous=state->mode;
        if (previous==0 && D_0036BB98.time>state->deadline)
            func_0016D480(state,1);
    } while (state->mode!=previous);
    {
        AttachmentOwner *owner=state->owner;
        AttachmentPosition *attachment=owner->attachment;
        AttachmentMatrixMethod *method=&owner->table[36];
        const AttachmentMatrix *matrix=method->get((char *)owner+method->adjustment);
        attachment->position=matrix->rows[3];
    }
}
