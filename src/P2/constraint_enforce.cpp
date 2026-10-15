// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct ConstraintNode;
struct ConstraintList { ConstraintNode *head,*tail; int linkOffset; };
struct ConstraintNode {
    int kind;
    float lowerBound,upperBound,force,residual,deltaResidual;
    float *response;
    int opaque1C;
    ConstraintNode *next,*previous;
};
struct ConstraintGroup {
    int capacity,count;
    ConstraintNode *nodes;
    ConstraintList positive,zero,maximum,uncategorized;
    int activeCount;
    float *matrix,*factors,*rhs,*deltaForce;
};
typedef char NodeHas40Bytes[(sizeof(ConstraintNode)==40)?1:-1];
typedef char GroupHas80Bytes[(sizeof(ConstraintGroup)==80)?1:-1];
extern "C" {
void func_0011B028(ConstraintList *,void *);
void func_0011AF60(ConstraintList *,void *);
void func_0011A278(int,float *,float *);
void func_0011A608(int,float *,float *,float *);
}
static inline float MaxScalar(float a,float b)
{
    float result;
    __asm__("max.s %0,%1,%2" : "=f"(result) : "f"(a),"f"(b));
    return result;
}
extern "C" void func_0011B4B0(ConstraintGroup *group,ConstraintNode *added)
{
    int i;
    if (added) {
        func_0011B028(&group->uncategorized,added);
        func_0011AF60(&group->positive,added);
        group->activeCount++;
    }
    for (int iteration=0;iteration<20;iteration++) {
        float *out=group->matrix;
        ConstraintNode *row;
        for (row=group->positive.head;row;row=row->next)
            for (ConstraintNode *column=group->positive.head;column;column=column->next)
                *out++=row->response[column-group->nodes];
        func_0011A278(group->activeCount,group->matrix,group->factors);
        float *rhs=group->rhs;
        for (row=group->positive.head;row;row=row->next)
            *rhs++=-row->residual;
        func_0011A608(group->activeCount,group->factors,group->rhs,group->deltaForce);
        for (i=0;i<group->count;i++) {
            float sum=0.0f;
            float *delta=group->deltaForce;
            for (row=group->positive.head;row;row=row->next)
                sum+=*delta++*row->response[i];
            group->nodes[i].deltaResidual=sum;
        }
        ConstraintNode *limited=0;
        float step=1.0f;
        int limitKind=0;
        float *delta=group->deltaForce;
        for (row=group->positive.head;row;row=row->next) {
            float change=*delta++;
            if (change>0.0001f) {
                if (row->upperBound==3.402823466e38f)
                    continue;
                float candidate=(row->upperBound-row->force)/change;
                if (candidate<step) {
                    step=candidate;
                    limited=row;
                    limitKind=4;
                }
            } else if (change<-0.0001f) {
                if (row->lowerBound==-3.402823466e38f)
                    continue;
                float candidate=(row->lowerBound-row->force)/change;
                if (candidate<step) {
                    step=candidate;
                    limited=row;
                    limitKind=2;
                }
            }
        }
        for (ConstraintNode *inactive=group->zero.head;inactive;inactive=inactive->next) {
            if (inactive->deltaResidual>-0.0001f)
                continue;
            float candidate=MaxScalar(-inactive->residual/inactive->deltaResidual,0.0f);
            if (candidate<0.0f)
                continue;
            if (candidate<step) {
                step=candidate;
                limited=inactive;
                limitKind=1;
            }
        }
        for (ConstraintNode *saturated=group->maximum.head;saturated;saturated=saturated->next) {
            if (saturated->deltaResidual<0.0001f)
                continue;
            float candidate=MaxScalar(-saturated->residual/saturated->deltaResidual,0.0f);
            if (candidate<step) {
                step=candidate;
                limited=saturated;
                limitKind=3;
            }
        }
        for (i=0;i<group->count;i++) {
            ConstraintNode *node=&group->nodes[i];
            node->residual+=step*node->deltaResidual;
        }
        delta=group->deltaForce;
        for (row=group->positive.head;row;row=row->next)
            row->force+=step * *delta++;
        switch (limitKind) {
        case 0:
            return;
        case 2:
            group->activeCount--;
            func_0011B028(&group->positive,limited);
            func_0011AF60(&group->zero,limited);
            if (limited==added)
                return;
            break;
        case 1:
            group->activeCount++;
            func_0011B028(&group->zero,limited);
            func_0011AF60(&group->positive,limited);
            break;
        case 4:
            group->activeCount--;
            func_0011B028(&group->positive,limited);
            func_0011AF60(&group->maximum,limited);
            if (limited==added)
                return;
            break;
        case 3:
            group->activeCount++;
            func_0011B028(&group->maximum,limited);
            func_0011AF60(&group->positive,limited);
            break;

        }
    }
}
