// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct CostMinimumInput {
    void *state;
    void *curve;
};
struct CostMinimumQuery {
    void *state;
    void *curve;
    float clearance;
    int reserved;
    qword point;
};
struct CostMinimumActor {
    char unaccessed[0x1130];
    float clearance;
};
typedef float (*CostObjective)(void *, float);
extern struct CostMinimumActor *D_00370AC0;
void func_0022E330(void *curve, void *point, void *direction);
qword func_001C9428(void *source, void *destination, qword point);
float func_001BB830(void *context, float parameter);
void func_0011EF00(CostObjective objective, void *context,
                  float initial, float step, float lower, float upper, float tolerance,
                  float *out_parameter, float *out_value);

float func_001BB860(struct CostMinimumInput *input)
{
    void *curve = input->curve;
    qword point[1];
    struct CostMinimumQuery query;
    float cost;
    func_0022E330(curve, point, 0);
    query.state = input->state;
    query.curve = curve;
    query.clearance = D_00370AC0->clearance;
    query.reserved = 0;
    query.point = func_001C9428(0, curve, point[0]);
    func_0011EF00(func_001BB830, &query,
                  0.5f, 0.25f, 0.25f, 3.0f, 0.1f, 0, &cost);
    return cost;
}
