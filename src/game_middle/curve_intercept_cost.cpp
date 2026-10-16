// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "common.h"

struct CurveInterceptState { void *owner; };
class CurveInterceptPrefix { public: char unaccessed[0x180]; };
class CurveInterceptInterface {
public:
    int unaccessed[9];
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Sample(void *owner, qword *point, float *angle, float parameter);
};
class CurveInterceptObject : public CurveInterceptPrefix, public CurveInterceptInterface {};
struct CurveInterceptContext {
    CurveInterceptState *state;
    CurveInterceptObject *curve;
    int word8, wordC;
    qword point;
};

extern "C" {
extern qword D_00317560;
void func_001BB228(void *state, qword initial_velocity, void *curve,
                  qword position, qword velocity, float *out_time,
                  float *out_cost, qword *out_position, qword *out_velocity);

float func_001BB7B0(void *context, float parameter)
{
    CurveInterceptContext *query = (CurveInterceptContext *)context;
    qword point;
    float cost;
    query->curve->Sample(query->state->owner, &point, 0, parameter);
    func_001BB228(query->state, query->point, query->curve,
                  point, D_00317560, 0, &cost, 0, 0);
    return cost;
}
}
