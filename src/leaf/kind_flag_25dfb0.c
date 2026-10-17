// SLY3_CFLAGS: -Os -G0
struct Holder { unsigned char prefix[0x441C]; int kind; int flag; };
extern int D_0036DBE0;
extern int D_0036DBA0;
extern unsigned char D_00468D30[];
int func_0025E160(int kind);
int func_0025E4A0(int mode,unsigned char *buffer);
void func_0025DFB0(struct Holder *holder,int kind)
{
    int result;
    int diff;
    int level;
    int *flagp=&holder->flag;
    holder->kind=kind;
    result=func_0025E160(kind);
    *flagp=result;
    diff=D_0036DBE0^2;
    if(!diff) {
        holder->flag=0;
        return;
    }
    if(result!=8)
        return;
    level=D_0036DBA0;
    if(level==-1) {
        if(func_0025E4A0(1,D_00468D30))
            return;
        if(holder->kind==0x23)
            holder->flag=1;
    } else if(level>=-1) {
        if(level<0x70C) {
            if(level>0x705)
                holder->flag=1;
        }
    }
}
