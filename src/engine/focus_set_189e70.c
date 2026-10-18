// SLY3_CFLAGS: -Os -G0
struct GameView { unsigned char prefix[0x4044]; void *panel; };
struct FocusIds { unsigned char prefix[0x1498]; int first, second, third; };
extern unsigned char D_004BC230[];
extern unsigned char D_00475480[];
extern struct FocusIds D_0036C700;
void func_00284568(void *object);
void *func_0017E1B8(void *game, int kind, int id, int flag);
void func_00189F38(void *object, int mode);
void func_00187118(void *panel);
void func_00289070(void *game, void *request, int word, int flags, int extra);
void func_00189E70(void *receiver, void *request, int identifier, int mode)
{
    void *object;
    struct GameView *game;
    func_00284568(D_004BC230);
    object = func_0017E1B8(D_00475480, 0x105, identifier, 0);
    if(object) {
        func_00189F38(object, mode);
        return;
    }
    game = (struct GameView *)D_00475480;
    if(game->panel) func_00187118(game->panel);
    D_0036C700.first = -1;
    D_0036C700.second = -1;
    D_0036C700.third = identifier;
    func_00289070(game, request, 0x1A8, mode | 6, -1);
}
