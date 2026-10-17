// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475480[];
struct Game { unsigned char prefix[0x4044]; void *active; };
int func_0025E150(void);
int func_00186200(void *receiver,int identity);
int func_0018ADB0(void)
{
    struct Game *game=(struct Game *)D_00475480;
    if(game->active) return func_00186200(game->active,func_0025E150())==1;
    return 0;
}
