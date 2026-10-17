// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
void func_0018B1E0(void);
void func_00164A98(void *self,int word,Qword a,Qword b,int c,int d);
struct ForwardRoot { unsigned char prefix[0xA4]; int expected; };
struct ForwardSelf { struct ForwardRoot *root; unsigned char gap4[0x84-4]; int word84; unsigned char gap88[0xC0-0x88]; int current; };
void func_00164A10(struct ForwardSelf *self,Qword a,Qword b,int c,int d)
{
    if(self->current!=self->root->expected) func_0018B1E0();
    func_00164A98(self,self->word84,a,b,c,d);
}
