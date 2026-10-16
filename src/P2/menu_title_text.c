// SLY3_CFLAGS: -Os -G0
struct MenuRow { int record; int unused; };
struct MenuState { char unknown_0[0x5C]; struct MenuRow rows[67]; int unknown_274; int page; };
struct RecordKind { char unknown_0[0x1C]; int title; char unknown_20[0x3C-0x20]; };
extern struct MenuState D_0046F810;
extern struct RecordKind D_00343098[];
extern char D_00475480[];
const unsigned short *func_00150630(void *game,int string_id);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *source);
void func_002209E8(unsigned short *output,int row)
{
    unsigned int kind=D_0046F810.rows[D_0046F810.page+row].record;
    int title=-1;
    if(kind<0x43)
        title=D_00343098[kind].title;
    if(title!=-1)
        func_00271730(output,func_00150630(D_00475480,title));
}
