// SLY3_CFLAGS: -Os -G0
extern int D_0036DBE0;
int func_00239E70(void *token);
int func_001F43C8(void *self);
struct QueryOther { unsigned char prefix[0x4A8]; void *token; };
struct QuerySelf { unsigned char prefix[0x190]; int word190; unsigned char gap194[0x198-0x194]; int word198; unsigned char gap19C[0x1FC-0x19C]; int word1FC; unsigned char gap200[0x424-0x200]; int word424; };
void func_001459D0(struct QuerySelf *self,struct QueryOther *other,int *out1,int *out2)
{
    *out1=0;
    *out2=0;
    if(self->word198==0) {
        if(other->token) {
            if(func_00239E70(other->token)!=0x1A0) { *out1=1; return; }
        }
        {
            int notmode=(D_0036DBE0!=2);
            if(!notmode) {
                int mine=func_001F43C8(self);
                if(func_001F43C8(other)>=mine) *out1=1;
                else *out2=func_001F43C8(self)-1;
            } else {
                *out2=self->word1FC;
            }
        }
    } else if(self->word190==1) {
        if(self->word424==0) *out1=1;
    }
}
