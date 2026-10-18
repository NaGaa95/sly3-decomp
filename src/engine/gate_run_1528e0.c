// SLY3_CFLAGS: -Os -G0
struct GameView { unsigned char prefix[0x4FA4]; int flag4FA4; };
extern unsigned char D_00475480[];
int func_0025E188(void);
int func_0025E150(void);
int func_001569B8(void *self);
void func_001853D8(void *game);
void *func_002459F8(int id);
void func_00244F08(void *object, void *owner);
void *func_001F4A80(void *self);
void func_00168670(void *object, int flag);
void func_001528E0(void *self)
{
    struct GameView *game;
    if(func_0025E188() == 1 && func_0025E150() == 0x23) return;
    if(func_001569B8(self)) return;
    game = (struct GameView *)D_00475480;
    if(!game->flag4FA4) func_001853D8(game);
    func_00244F08(func_002459F8(0x2A), 0);
    func_00168670(func_001F4A80(self), 0);
}
