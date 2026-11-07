// Sly 2 counterpart: cmd_sem_init (decomp src/lib/cmd_sem_init.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned attr; unsigned option; } ee_sema_t;
extern int D_0034C3A0, D_0034C3A8, D_0034C3AC, D_0034C3B0, D_0034C3B4;
extern char D_0032B568[], D_0032B578[], D_0032B588[], D_0032B598[];
int func_002936A0(ee_sema_t *);
void func_002A0028(void)
{
    ee_sema_t s;
    if (D_0034C3A8 == -1 || D_0034C3AC == -1 || D_0034C3B0 == -1) {
        s.init_count = 1;
        s.option = (unsigned)D_0032B568;
        s.max_count = 1;
        D_0034C3A8 = func_002936A0(&s);
        s.option = (unsigned)D_0032B578;
        D_0034C3AC = func_002936A0(&s);
        s.option = (unsigned)D_0032B588;
        D_0034C3B0 = func_002936A0(&s);
        s.option = (unsigned)D_0032B598;
        { ee_sema_t *p = &s; /* empty asm: Sony sched keeps a0=&s before the store */ __asm__ __volatile__("" : "+r"(p)); s.init_count = 0; D_0034C3A0 = func_002936A0(p); }
        __asm__ __volatile__("");
        D_0034C3B4 = 0;
    }
}
