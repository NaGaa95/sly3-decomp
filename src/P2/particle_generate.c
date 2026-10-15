// Ordinary particle-array construction; hardware helpers express packed math.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Request { int bytes, alignment; };
union Workspace { struct Request request; qword direction; };
struct Sampling { int count; float tilt_step,pan_step,tilt,pan; };
struct Limits { float low,high; };
struct Motion { qword origin,axis[3],linear,angular; };
struct Emitter {
    char prefix[0x1C]; struct Motion *motion;
    char prefix2[0x84-0x20]; int requested;
    char prefix3[0x90-0x88]; struct Limits limits;
};
struct Outputs { qword *position,*velocity; float *birth,*death; int relative; };
void *func_001D25B0(struct Request *request);
void func_00178C08(int,struct Limits *,int,struct Sampling *);
void func_001785E8(struct Emitter *,int,int,qword *,qword *);
void func_00178E98(void *,struct Sampling *,void *,int,qword *,qword *,qword *,float *,float *);
void func_00178B20(struct Emitter *,qword *,qword *);
static __inline__ void *AllocateAligned(union Workspace *workspace,int bytes)
{
    workspace->request.bytes=bytes;
    workspace->request.alignment=16;
    return func_001D25B0(&workspace->request);
}
// The tied vector preserves its real W lane; the complete ACC.xyz chain is
// overwritten before use. No ACC value escapes this primitive.
static __inline__ qword Rotate(const qword *basis,qword vector)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
        : "+j"(vector) : "j"(basis[0]),"j"(basis[1]),"j"(basis[2]));
    return vector;
}
static __inline__ qword Add(qword a,qword b)
{
    qword result;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(a),"j"(b));
    return result;
}
static __inline__ qword Subtract(qword a,qword b)
{
    qword result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(a),"j"(b));
    return result;
}
// XYZ cross product, retaining the actual angular input W used by the packed
// final add. ACC.xyz is scratch only inside this complete operation.
static __inline__ qword Cross(qword angular,qword radius)
{
    __asm__("vopmula.xyz $ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0"
        : "+j"(angular) : "j"(radius));
    return angular;
}
void func_001795F8(int count,struct Emitter *emitter,struct Outputs *out)
{
    union Workspace workspace;
    struct Sampling sampling;
    int i;
    out->position=(qword *)AllocateAligned(&workspace,count*sizeof(qword));
    out->velocity=(qword *)AllocateAligned(&workspace,count*sizeof(qword));
    out->birth=(float *)AllocateAligned(&workspace,count*sizeof(float));
    out->death=(float *)AllocateAligned(&workspace,count*sizeof(float));
    func_00178C08(emitter->requested,&emitter->limits,count,&sampling);
    for(i=0;i<count;++i) {
        struct Motion *motion;
        func_001785E8(emitter,i,count,&out->position[i],&workspace.direction);
        func_00178E98((char *)emitter+0x50,&sampling,(char *)emitter+0x10,i,
            &out->position[i],&workspace.direction,&out->velocity[i],&out->birth[i],&out->death[i]);
        motion=emitter->motion;
        if(motion) {
            out->position[i]=Add(Rotate(motion->axis,out->position[i]),motion->origin);
            out->velocity[i]=Add(Add(Rotate(motion->axis,out->velocity[i]),motion->linear),
                Cross(motion->angular,Subtract(out->position[i],motion->origin)));
        }
        if(out->relative)
            func_00178B20(emitter,&out->position[i],&out->velocity[i]);
    }
}
