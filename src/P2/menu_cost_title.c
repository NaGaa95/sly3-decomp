// SLY3_CFLAGS: -Os -G0
struct MenuRow { int record; int unused; };
struct MenuState { char unknown_0[0x5C]; struct MenuRow rows[67]; int unknown_274; int page; };
struct RecordCost { int count; int text; int unused; };
extern struct MenuState D_0046F810;
extern struct RecordCost D_00349070[];
extern char D_00475480[];
const unsigned short *func_00150630(void *game,int string_id);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *source);
void func_00220AF0(unsigned short *output,int row)
{
    unsigned int kind=D_0046F810.rows[D_0046F810.page+row].record;
    if(kind<0x40) {
        int text=D_00349070[kind].text;
        if(text!=-1)
            func_00271730(output,func_00150630(D_00475480,text));
    }
}
