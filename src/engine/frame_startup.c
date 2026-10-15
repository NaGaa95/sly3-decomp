// SLY3_CFLAGS: -Os -G0
struct StartupListView { void *first; void *last; int link_offset; };
int func_00293380(int cause,int (*handler)(int cause),int next);
int func_00293DF8(int cause);
int func_00271B20(int initial_count,int maximum_count);
void func_0011AF38(struct StartupListView *list,int link_offset);
int func_00294260(int thread_id,void *argument);
int func_0018DE80(int unused_cause);
extern int D_0036C684;
extern int D_0036C688;
extern struct StartupListView D_0036C658;
extern struct StartupListView D_0036C668;
extern int D_00349F8C;

void func_00182BE0(void)
{
    func_00293380(5,func_0018DE80,0);
    func_00293DF8(5);
    D_0036C684 = func_00271B20(0,2);
    D_0036C688 = func_00271B20(2,2);
    func_0011AF38(&D_0036C658,0x444);
    func_0011AF38(&D_0036C668,0x1090);
    func_00294260(D_00349F8C,0);
}
