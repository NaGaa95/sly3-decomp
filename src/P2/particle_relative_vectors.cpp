// Sly 2 func_0015AD48; Sly 3 uses query slot37 and modes0/1/2.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ParticleWord __attribute__((mode(TI)));
struct ParticleMatrix { ParticleWord rows[4]; };
struct RelativeFrame { char prefix[0x40]; ParticleMatrix matrix; };
struct QueryBuffer { ParticleWord rows[4]; };
struct RelativeEntry { short delta, reserved; RelativeFrame *(*query)(void *,QueryBuffer *); };
struct RelativeObject { char prefix[12]; RelativeEntry *table; };
struct RelativeMode { int first, second, mode; };
struct ParticleRelativeInput { int first, second; RelativeObject **objects; int fourth; RelativeMode relative; };
extern "C" ParticleMatrix *func_0011D558(ParticleMatrix *,const ParticleMatrix *,const QueryBuffer *);
extern "C" ParticleWord func_001C9828(ParticleMatrix *,const ParticleMatrix *,ParticleWord);
extern "C" ParticleWord func_001C98A0(ParticleMatrix *,const ParticleMatrix *,ParticleWord);
extern "C" ParticleWord func_0028BCD0(RelativeFrame *,void *,ParticleWord);

// One real packed XYZW add; output may alias either input. It neither reads nor
// modifies VU ACC or memory. Arithmetic status is not carried as a C++ value.
static __inline__ ParticleWord AddParticleVectors(ParticleWord left,ParticleWord right)
{
    ParticleWord result;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(left),"j"(right));
    return result;
}
extern "C" void func_00178B20(ParticleRelativeInput *input,ParticleWord *position,ParticleWord *velocity)
{
    RelativeMode *mode=&input->relative;
    RelativeObject *object=*input->objects;
    QueryBuffer query;
    ParticleMatrix matrix;
    RelativeFrame *frame;
    if(!object)return;
    RelativeEntry *entry=&object->table[37];
    frame=entry->query((char *)object+entry->delta,&query);
    func_0011D558(&matrix,&frame->matrix,&query);
    *position=func_001C9828(&matrix,0,*position);
    if(mode->mode!=2) {
        *velocity=func_001C98A0(&matrix,0,*velocity);
        if(mode->mode==0)
            *velocity=AddParticleVectors(*velocity,func_0028BCD0(frame,0,frame->matrix.rows[3]));
    }
}
