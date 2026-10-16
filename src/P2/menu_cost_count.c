// SLY3_CFLAGS: -Os -G0
struct MenuRow { int record; int unused; };
struct MenuState { char unknown_0[0x5C]; struct MenuRow rows[67]; int unknown_274; int page; };
struct RecordCost { int count; int text; int unused; };
extern struct MenuState D_0046F810;
extern struct RecordCost D_00349070[];
extern char D_003260C0[];
int func_00271448(char *output,const char *format,...);
unsigned short *func_00271828(unsigned short *destination,const char *source);
void func_00220B70(unsigned short *output,int row)
{
    char buffer[16];
    unsigned int kind=D_0046F810.rows[D_0046F810.page+row].record;
    int count=0;
    if(kind<0x40)
        count=D_00349070[kind].count;
    if(count) {
        func_00271448(buffer,D_003260C0,count);
        func_00271828(output,buffer);
    }
}
