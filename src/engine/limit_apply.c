// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef union { Qword packed; float lane[4]; } LimitVector;
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct LimitEntry { short delta,padding; int (*fn)(void *); };
struct LimitVectorEntry { short delta,padding; Qword (*fn)(void *); };
struct LimitSource { unsigned char prefix[0xC]; struct LimitVectorEntry *table; };
struct LimitLink { unsigned char prefix[0x4C]; struct LimitSource *source; };
struct LimitSelf {
    unsigned char prefix[0xC]; struct LimitEntry *table;
    unsigned char gap10[0x1BC-0x10]; float value;
    unsigned char gap1C0[0x218-0x1C0]; struct LimitLink *link;
};
float func_0011E560(float value,float limit);
void func_0023A9F0(void *owner,int context);
void func_0024E878(void *self,float value);
void func_00155AF0(struct LimitSelf *self)
{
    int context=self->table[111].fn((char *)self+self->table[111].delta);
    func_0023A9F0(*(void **)((char *)self+0x1140),context);
    if(self->link) {
        struct LimitSource *source=self->link->source;
        LimitVector vector;
        vector.packed=source->table[39].fn((char *)source+source->table[39].delta);
        vector.lane[2]=func_0011E560(vector.lane[2],10.0f);
        func_0024E878(self,self->value+vector.lane[2]*D_0036BB98.dt);
    }
}
