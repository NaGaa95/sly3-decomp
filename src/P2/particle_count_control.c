// Sly 2 SetEmitterParticleCount algorithm; Sly 3 has distinct inactive kind0.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
struct EmitterControl {
    char prefix[0xD0]; int dirty;
    char reservedD4[0xE0-0xD4]; int kind,count;
};
void func_00178150(struct EmitterControl *);
void func_00178160(struct EmitterControl *);
void func_00178200(struct EmitterControl *emitter,int count)
{
    int kind=emitter->kind;
    if(kind==-1)
        emitter->count=count;
    else if(kind==0) {
        /* Inactive Sly 3 state: the dirty write still follows. */
    } else if(kind==1) {
        if(count==0)
            func_00178150(emitter);
        else if(count==-1)
            func_00178160(emitter);
        else
            emitter->count=count;
    }
    emitter->dirty=1;
}
