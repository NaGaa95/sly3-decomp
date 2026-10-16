// SLY3_CFLAGS: -Os -G0
struct PanelMenu { unsigned char opaque00[0x18]; int selection; };
struct PanelMode { unsigned char opaque00[0x50]; int state; };
extern unsigned char D_0036C700[], D_0046FAA0[];
extern struct PanelMenu D_0046F550;
extern void *D_004794C4;
extern struct PanelMode *D_004BC244;
void func_001854C8(void *context, int event, void *payload);
void func_0021DDC0(void *panel, int selection);
void func_002214F0(void *panel, int state);

void func_001D5228(void *unused_choice)
{
    func_001854C8(D_0036C700, 0x3D, 0);
    func_0021DDC0(D_0046FAA0, D_0046F550.selection);
    if (D_004794C4) {
        int state = D_004BC244 ? D_004BC244->state : -1;
        if (state == 0 || state == 2)
            func_002214F0(D_0046FAA0, 2);
        else
            func_002214F0(D_0046FAA0, 1);
    } else {
        func_002214F0(D_0046FAA0, 0);
    }
}
