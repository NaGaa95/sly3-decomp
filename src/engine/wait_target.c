// SLY3_CFLAGS: -Os -G0
typedef int WaitTargetWord __attribute__((mode(TI)));
typedef union WaitTargetRow {
    WaitTargetWord raw;
    float lanes[4];
} WaitTargetRow;
typedef struct WaitTargetMatrix { WaitTargetRow rows[4]; } WaitTargetMatrix;
typedef struct WaitTargetMethod {
    short adjustment,reserved;
    const WaitTargetMatrix *(*matrix)(void *);
} WaitTargetMethod;
typedef struct WaitTargetObject {
    char unaccessed[0xC];
    WaitTargetMethod *table;
} WaitTargetObject;
int func_0013B500(void *object,int kind);
void func_0022EA88(void *object,WaitTargetWord fallback,const void *metric,
                   WaitTargetWord *position,WaitTargetWord *direction,
                   float *parameter,float *finalParameter);
float func_001205C8(WaitTargetWord direction);
float func_002A3EE8(float y,float x);
void func_001976B8(void *suppliedTemplate,WaitTargetWord fallback,
                   WaitTargetObject *object,WaitTargetWord *position,float *angle)
{
    WaitTargetWord point;
    WaitTargetWord direction;
    float result;
    if(object) {
        if(func_0013B500(object,9)) {
            func_0022EA88(object,fallback,0,&point,&direction,0,0);
            result=func_001205C8(direction);
        } else {
            WaitTargetMethod *method=&object->table[36];
            const WaitTargetMatrix *matrix=method->matrix((char *)object+method->adjustment);
            point=matrix->rows[3].raw;
            method=&object->table[36];
            matrix=method->matrix((char *)object+method->adjustment);
            result=func_002A3EE8(matrix->rows[0].lanes[1],matrix->rows[0].lanes[0]);
        }
    } else {
        point=fallback;
        result=0.0f;
    }
    if(position)
        *position=point;
    if(angle)
        *angle=result;
}
