// SLY3_CFLAGS: -Os -G0
typedef unsigned int CurveQueryValue __attribute__((mode(TI)));
struct CurveMinimumView {
    unsigned char prefix[0xD4];
    int wrap;
    int count;
    float *parameters;
};
struct CurveMinimumContext {
    struct CurveMinimumView *curve;
    int distanceKind;
    int reserved[2];
    CurveQueryValue query;
};
extern float D_00326DB0, D_00326DB4;
float func_0022E520(void *context, float parameter);
void func_0011EF00(float (*objective)(void *, float), void *context,
                  float initial, float step, float lower, float upper, float tolerance,
                  float *outParameter, float *outValue);
float func_0022DFF0(void *curve, float parameter);
void func_0022E148(void *curve, float parameter, void *position, void *direction);
float func_0022DD48(void *curve, float parameter);

void func_0022E938(struct CurveMinimumView *curve, CurveQueryValue query,
                  int distanceKind, void *position, void *direction,
                  float *progress, float *length, float initial)
{
    struct CurveMinimumContext context;
    float parameter;
    context.distanceKind=distanceKind;
    context.query=query;
    context.curve=curve;
    func_0011EF00(func_0022E520, &context, initial,
                  (curve->parameters[1]-curve->parameters[0])*0.1f,
                  curve->wrap?D_00326DB0:curve->parameters[0],
                  curve->wrap?D_00326DB4:curve->parameters[curve->count-1],
                  0.0f, &parameter, 0);
    parameter=func_0022DFF0(curve, parameter);
    if (position||direction)
        func_0022E148(curve, parameter, position, direction);
    if (progress)
        *progress=parameter;
    if (length)
        *length=func_0022DD48(curve, parameter);
}
