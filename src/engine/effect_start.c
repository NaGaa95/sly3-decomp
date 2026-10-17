// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317560;
struct StartEntry { short delta,padding; char *(*fn)(void *); };
struct StartTarget { unsigned char prefix[0xC]; struct StartEntry *table; };
struct StartSelf { unsigned char prefix[0x190]; int word190; int word194; void *word198; };
Qword *func_0019F2D0(void *self,Qword position);
void func_00240CB0(void *self,int a,void *target,int b,int c,int d,Qword e,Qword f,int g);
void func_00179E58(void *handle,int a,int b,Qword c,Qword d,float e,float f);
void func_0019E8F0(void *self,void *record,int mode);
void func_0019F4B0(struct StartSelf *self,struct StartTarget *target)
{
    Qword *record;
    if(target) {
        if(self->word190) {
            record=func_0019F2D0(self,*(Qword *)(target->table[36].fn((char *)target+target->table[36].delta)+0x30));
            func_00240CB0(self,0,target,0x100,self->word190,0,*record,D_00317560,0);
            if(self->word198) func_00179E58(self->word198,4,0,D_00317560,*record,0.0f,0.0f);
            func_0019E8F0(self,record,2);
            self->word194=0;
        }
    }
}
