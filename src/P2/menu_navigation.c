// SLY3_CFLAGS: -Os -G0
struct MenuNavigationView {
    unsigned char beforeNavigation[0x38];
    unsigned int navigation;
    float changedAt;
    unsigned char beforeMode[0x50-0x40];
    int menuMode;
    unsigned char beforeCount[0x58-0x54];
    int count;
    unsigned char beforeIndex[0x128-0x5C];
    int index;
};
struct MenuNavigationClock { unsigned char beforeEventTime[0x40]; float eventTime; };
struct S;
struct P;
extern struct MenuNavigationClock D_0036BB98;
extern unsigned char D_004BC230[];
void func_002214F0(void *owner,int mode);
void func_002210C0(struct S *owner,int index);
int func_002852B0(void *provider);
void *func_002459F8(int identifier);
void func_00244F08(struct P *sound,int mode);
void func_00221810(struct MenuNavigationView *owner,unsigned int state)
{
    if (state==owner->navigation) return;
    owner->navigation=state;
    owner->changedAt=D_0036BB98.eventTime;
    if (owner->menuMode==2) return;
    switch (state) {
    case 0:
        if (owner->count) func_002214F0(owner,1);
        break;
    case 4:
        if (!func_002852B0(D_004BC230)) func_002214F0(owner,0);
        break;
    case 1:
    case 2:
    case 3:
        if (owner->index>0) {
            func_002210C0((struct S *)owner,owner->index-1);
            func_00244F08((struct P *)func_002459F8(0x35),0);
        }
        break;
    case 5:
    case 6:
    case 7:
        if (owner->index<owner->count-1) {
            func_002210C0((struct S *)owner,owner->index+1);
            func_00244F08((struct P *)func_002459F8(0x35),0);
        }
        break;
    }
}
