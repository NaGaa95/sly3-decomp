// Per-frame UI update: service the pending select requests, refresh the menu focus when no cutscene mode is active, then update every panel in turn.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475480[];
extern unsigned char D_0046F550[], D_0046F810[], D_0046F7A0[], D_0036BB88[], D_004C4090[], D_0046F770[];
extern unsigned char D_0046FAA0[], D_0046FD00[], D_003751D0[], D_00375240[], D_0046FBE0[], D_0046FC30[], D_0046FC90[];
extern int D_0036DBE0;
int func_001D4808(void);
int func_001A7890(int mask);
int func_001A7900(int mask, int count);
int func_001A9568(void *game, int id);
int func_001A9478(void *game, int id);
int func_001A9538(void *game, int id);
int func_001A79F0(int id);
void *func_001F4AD0(void *game, int id);
int func_0021EE68(void *panel, void *object);
void func_0021FA38(void *panel, int id);
void func_001D48D0(int id);
int func_0011B0F0(void *list);
void func_001D3288(void *menu);
void func_0021FE98(void *panel);
void func_0021EEF8(void *panel);
void func_00164028(void *clock);
void func_00288D60(void *queue);
void func_0021E710(void *panel);
void func_00220E80(void *panel);
void func_00222E48(void *panel);
void func_001D0DC8(void *panel);
void func_001D2178(void *panel);
void func_0021EBE0(void *panel);
void func_00221C08(void *panel);
void func_00222B60(void *panel);

void func_0021D9E0(void *list)
{
    int id;
    if (func_001D4808()) {
        id = func_001A7890(0x800);
        if (id != -1 && func_001A9568(D_00475480, id)) func_001D48D0(id);
    }
    if (func_001D4808()) {
        id = func_001A7900(0x100, 8);
        if (id != -1 && func_001A9568(D_00475480, id) &&
            func_0021EE68(D_0046F7A0, func_001F4AD0(D_00475480, id)))
            func_0021FA38(D_0046F7A0, id);
    }
    {
        int notCutscene = D_0036DBE0 ^ 2;
    if (notCutscene) {
        if (func_001D4808()) {
            int first = func_001A9478(D_00475480, 0) == 0;
            int second = func_001A9538(D_00475480, 0) == 0;
            int third = func_0011B0F0(list);
            int fourth = func_001A79F0(0);
            if (first && second && third && fourth) func_001D48D0(0);
        }
    }
    }
    func_001D3288(D_0046F550);
    func_0021FE98(D_0046F810);
    func_0021EEF8(D_0046F7A0);
    func_00164028(D_0036BB88);
    func_00288D60(D_004C4090);
    func_0021E710(D_0046F770);
    func_00220E80(D_0046FAA0);
    func_00222E48(D_0046FD00);
    func_001D0DC8(D_003751D0);
    func_001D2178(D_00375240);
    func_0021EBE0(D_0046FBE0);
    func_00221C08(D_0046FC30);
    func_00222B60(D_0046FC90);
}
