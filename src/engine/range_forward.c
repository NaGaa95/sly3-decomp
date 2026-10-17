// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00479350;
struct FwdEntry { short delta,padding; char *(*fn)(void *); };
struct FwdReceiver { unsigned char prefix[0xC]; struct FwdEntry *table; };
struct FwdSelf { unsigned char prefix[0x104]; float f104; unsigned char gap108[0x130-0x108]; float f130; struct FwdReceiver *first; struct FwdReceiver *second; };
void func_001C8328(void *self,Qword a,Qword b,Qword c,float x,float y);
void func_0013CF10(struct FwdSelf *self)
{
    if(self->first) {
        if(self->second) {
            Qword a=D_00479350;
            Qword b=*(Qword *)(self->first->table[36].fn((char *)self->first+self->first->table[36].delta)+0x30);
            Qword c=*(Qword *)(self->second->table[36].fn((char *)self->second+self->second->table[36].delta)+0x30);
            func_001C8328(self,a,b,c,self->f130,self->f104);
        }
    }
}
