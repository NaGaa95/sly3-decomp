// SLY3_CFLAGS: -Os -G0
extern int D_0036DB98;
struct EngineCurrentSub { unsigned char prefix[0x18]; int id; };
struct EngineCurrentGame { unsigned char prefix[0x4044]; struct EngineCurrentSub *current; };
void func_001B67C0(void *game,int a,int b,int c);
void func_0018AA48(struct EngineCurrentGame *game,struct EngineCurrentSub *sub)
{
    if(sub) D_0036DB98=sub->id; else D_0036DB98=-1;
    if(sub!=game->current) func_001B67C0(game,0,0,0);
    game->current=sub;
}
