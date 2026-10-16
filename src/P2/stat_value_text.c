// SLY3_CFLAGS: -Os -G0
struct StatEntry { int value; int unused; };
struct StatScreen { char unknown_0[0x70]; struct StatEntry entries[4]; int unknown_90; int count; };
extern struct StatScreen *D_00468D24;
extern char D_00325DF8[];
int func_00271448(char *output,const char *format,...);
unsigned short *func_002717E0(unsigned short *destination,const char *source);
void func_0021A7B8(unsigned short *output,int index)
{
    char buffer[16];
    struct StatScreen *screen=D_00468D24;
    if(index<screen->count) {
        func_00271448(buffer,D_00325DF8,screen->entries[index].value);
        func_002717E0(output,buffer);
    }
}
