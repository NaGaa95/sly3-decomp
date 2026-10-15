// SLY3_CFLAGS: -Os -G0
typedef int PackedPosition __attribute__((mode(TI)));
struct FrameMatrix { PackedPosition row[4]; };
struct MatrixEntry { short delta, reserved; struct FrameMatrix *(*get)(void *); };
struct FrameActor { char prefix[0xC]; struct MatrixEntry *table; };
struct FrameOutput { char prefix[0x44]; float first, negativeSecond, second; };
struct FramePolynomial { float constant, linear, quadratic, reserved; };
struct FramePositionState {
    char prefix[0x10]; int enabled;
    char pad14[0x6C - 0x14]; int pending; float amount; void *attachment;
    char pad78[8]; struct FramePolynomial first, second;
};
struct FrameGame { char prefix[0x47BC]; struct FrameOutput *output; };
extern struct FrameGame D_00475480;
extern void *func_001F4AD0(void *, int);
extern int func_0013B500(void *, int);
extern int func_00291D30(int,int,int,int,int,int,int,int,long);
extern void func_00246DE0(int, long);
extern void func_00173E48(void *,PackedPosition,int,void **);
typedef char CheckPosition16[sizeof(PackedPosition)==16?1:-1];
typedef char CheckMatrix64[sizeof(struct FrameMatrix)==64?1:-1];
typedef char CheckStateA0[sizeof(struct FramePositionState)==0xA0?1:-1];
typedef char CheckPointer4[sizeof(void *)==4?1:-1];
typedef char CheckContext8[sizeof(long)==8?1:-1];
static inline float EvaluateFramePolynomial(struct FramePolynomial *polynomial,float amount) {
    return polynomial->constant + amount * (polynomial->linear + amount * polynomial->quadratic);
}
void func_002479C8(void *receiver) {
    struct FramePositionState *state=(struct FramePositionState *)receiver;
    struct FrameOutput *output;
    struct FrameActor *actor;
    PackedPosition position;
    if (!state->enabled) {
        state->amount=0.0f;
    } else if (!state->pending) {
        state->pending=1;
        func_00291D30(0x524B5553,11,0,0,0,0,0,(int)func_00246DE0,(long)state);
    }
    output=0;
    actor=(struct FrameActor *)func_001F4AD0(&D_00475480,0);
    if (actor && func_0013B500(actor,0x33) && 0.5f < state->amount) {
        struct MatrixEntry *entry=&actor->table[36];
        float second;
        output=D_00475480.output;
        position=entry->get((char *)actor+entry->delta)->row[3];
        output->first=EvaluateFramePolynomial(&state->first,state->amount);
        second=EvaluateFramePolynomial(&state->second,state->amount);
        output->second=second;
        output->negativeSecond=-second;
    }
    func_00173E48(output,position,(int)actor,&state->attachment);
}
