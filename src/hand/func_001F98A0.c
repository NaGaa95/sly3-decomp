// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct TP { int status; void *func; void *stack; int stack_size; void *gp_reg; int initial_priority; int pad[6]; };
struct G { char pad[0x10]; int tid; };
extern struct G D_00349F88;
extern char D_00467BF0[];
extern char D_00372DF0[];
extern int D_00467BE0, D_00467BE4, D_00467BE8;
void func_001F9960(void *);
void func_00292034(void *p, int c, int cb);
int func_002934A0(struct TP *ptp);
int func_00271B20(int a, int b);
int func_00294260(int tid, void *arg);
void func_001F98A0(void)
{
    struct TP tp;
    func_00292034(&tp, 0, sizeof(tp));
    tp.stack_size = 0x1000;
    tp.stack = D_00467BF0;
    tp.gp_reg = D_00372DF0;
    tp.initial_priority = 4;
    tp.func = func_001F9960;
    D_00349F88.tid = func_002934A0(&tp);
    D_00467BE0 = func_00271B20(0, 1);
    D_00467BE4 = func_00271B20(0, 1);
    D_00467BE8 = func_00271B20(0, 1);
    func_00294260(D_00349F88.tid, 0);
}
