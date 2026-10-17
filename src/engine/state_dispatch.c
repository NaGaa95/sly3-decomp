// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00321A80,D_00321A90;
void func_00238AE0(void);
void func_0018C428(void *a,void *b,int count,Qword value);
struct StateSelf { unsigned char prefix[0x34]; int state; unsigned char gap38[0x44-0x38]; char *buffer; unsigned char gap48[0x50-0x48]; void *first; unsigned char gap54[0x58-0x54]; void *second; char third[1]; };
void func_0018C510(struct StateSelf *self)
{
    func_00238AE0();
    switch(self->state) {
    case 3:
        func_0018C428(self->first,self->buffer+4,4,D_00321A80);
        break;
    case 5:
    case 6:
        func_0018C428(self->second,self->third,4,D_00321A90);
        break;
    }
}
