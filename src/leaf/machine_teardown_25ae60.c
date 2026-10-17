// SLY3_CFLAGS: -Os -G0
struct Player { char storage[0x11C0]; };
extern struct Player D_0036E740[];
extern char D_0036C700[];
extern char D_0036C6E8[];
extern char D_0046F540[];
extern char D_004BC230[];
extern char D_00474FF0[];
extern int D_00370AC0, D_0038AE90, D_0036B250, D_0046FF30, D_0038AE94, D_0038AE98, D_0036B334, D_00468D08, D_00468D04, D_0036BB80, D_00475470, D_00468D24;
struct Machine { unsigned char prefix[0x4050]; void *list; unsigned char gap4054[0x4FB0-0x4054]; int word4FB0; };
struct Controller { unsigned char prefix[0x16C]; int first; unsigned char gap170[4]; int second; };
void func_00187118(void *list);
void *func_001F4B30(void *receiver);
int func_0013B500(void *object,int kind);
int *func_00185720(char *table,void *request);
void func_001F4B00(void *unused,int index,void *object);
void func_0021D7A0(void *list);
void func_002499C8(void *reference);
void func_00189140(void *object);
void func_001849E8(void *object);
void func_00283790(void *object);
void func_00247650(void *object);
void func_00235E28(void);
void func_001A7840(void);
void func_001D2598(void);
void func_0025AE60(struct Machine *machine)
{
    int i;
    if(machine->list) {
        func_00187118(machine->list);
        machine->list=0;
    }
    for(i=0;i<2;i++) {
        struct Controller *controller=func_001F4B30(&D_0036E740[i]);
        if(controller && func_0013B500(controller,0x33)) {
            int *entry=func_00185720(D_0036C700,controller);
            entry[0]=controller->first;
            entry[1]=controller->second;
        }
        func_001F4B00(machine,i,0);
    }
    func_0021D7A0(D_0046F540);
    func_002499C8(machine);
    func_00189140(D_0036C6E8);
    func_001849E8(D_0036C700);
    func_00283790(D_004BC230);
    func_00247650(D_00474FF0);
    func_00235E28();
    func_001A7840();
    machine->word4FB0=0;
    D_00370AC0=0;
    D_0038AE90=0;
    D_0036B250=0;
    D_0046FF30=0;
    D_0038AE94=0;
    D_0038AE98=0;
    D_0036B334=0;
    D_00468D08=0;
    D_00468D04=0;
    D_0036BB80=0;
    D_00475470=0;
    D_00468D24=0;
    func_001D2598();
}
