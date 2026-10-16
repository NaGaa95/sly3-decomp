// SLY3_CFLAGS: -Os -G0
typedef int WaitPositionWord __attribute__((mode(TI)));
typedef struct WaitPositionMatrix { WaitPositionWord rows[4]; } WaitPositionMatrix;
typedef struct WaitPositionMethod {
    short adjustment,reserved;
    const WaitPositionMatrix *(*matrix)(void *);
} WaitPositionMethod;
typedef struct WaitPositionOwner {
    char unaccessed[0xC];
    WaitPositionMethod *table;
} WaitPositionOwner;
typedef struct WaitPositionState {
    char unaccessed[0x10];
    WaitPositionOwner *owner;
    char unaccessed14[0x30-0x14];
    void *current;
} WaitPositionState;
void func_001976B8(void *suppliedTemplate,WaitPositionWord fallbackPosition,
                   void *object,WaitPositionWord *position,float *angle);
void func_00198250(WaitPositionState *state,void *object,
                   WaitPositionWord *position,float *angle)
{
    WaitPositionOwner *owner=state->owner;
    WaitPositionMethod *method=&owner->table[36];
    const WaitPositionMatrix *matrix=method->matrix((char *)owner+method->adjustment);
    func_001976B8(state->current,matrix->rows[3],object,position,angle);
}
