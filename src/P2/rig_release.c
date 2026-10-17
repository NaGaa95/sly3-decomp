// SLY3_CFLAGS: -Os -G0
typedef int Vec128 __attribute__((mode(TI)));
struct Method { short delta,unused; Vec128 *(*method)(void); };
struct Part { unsigned char prefix[0xC]; struct Method *methods; };
struct Rig { unsigned char prefix[0x58]; struct { struct Part *part; int unknown; } slots[1]; };
struct RigState { unsigned char prefix[0x270]; void *target; int unknown_274; };
void func_00279450(void *rig,int mode);
void func_00279960(void *target,Vec128 value);
void func_002793F0(struct Rig *rig)
{
    struct RigState *state=(struct RigState *)rig;
    struct Part *part;
    Vec128 *result;
    func_00279450(rig,0);
    part=rig->slots[*(int *)((char *)rig+0x278)-1].part;
    result=((Vec128 *(*)(void *))part->methods[36].method)((char *)part+part->methods[36].delta);
    func_00279960(state->target,result[3]);
    state->unknown_274=0;
}
