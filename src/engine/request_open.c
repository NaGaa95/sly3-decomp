// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475480[];
struct EngineRequestGame { unsigned char prefix[0x4044]; void *active; unsigned char gap[0x4428-0x4048]; int value; };
void func_00289070(void *context,void *record,int id,int option,int selection);
void func_001855F0(int unused,int kind)
{
    if(kind==12) {
        struct EngineRequestGame *game=(struct EngineRequestGame *)D_00475480;
        if(!game->active) func_00289070(game,0,game->value,0,0x36B);
    }
}
