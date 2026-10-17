// SLY3_CFLAGS: -Os -G0
typedef unsigned int PositionBits __attribute__((mode(TI)));
float func_00167FE8(void *owner,PositionBits position);
struct State;
int func_00168098(const struct State *owner,float distance,float limit,float *output);
int func_00168048(void *owner,PositionBits position,float *output,float limit)
{
    float distance=func_00167FE8(owner,position);
    return func_00168098(owner,distance,limit,output);
}
