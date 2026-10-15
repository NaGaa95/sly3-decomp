// SLY3_CFLAGS: -Os -G0
struct MovieWorkerSetupState {
    unsigned char opaque00[0x114];
    void *stream;
    unsigned char opaque118[0x23C - 0x118];
    int semaphore;
};
struct MovieThreadParameters {
    int word00;
    void (*entry)(void *);
    void *stack;
    int stack_bytes;
    void *gp;
    int initial_priority;
    int words18[6];
};
extern struct MovieWorkerSetupState D_00389AC0;
extern unsigned char D_00389E90[], D_00372DF0[];
extern int D_00349F94;
int func_00271B20(int initial_count, int maximum_count);
void *func_00292034(void *, int, unsigned int);
int func_002934A0(struct MovieThreadParameters *);
int func_00294260(int thread_id, void *argument);
void func_001DAA08(void *unused_start_argument);

typedef char MovieThreadParameterSize[(sizeof(struct MovieThreadParameters) == 48) ? 1 : -1];

void func_001DAB48(void)
{
    struct MovieThreadParameters parameters;
    D_00389AC0.semaphore = func_00271B20(0, 1);
    D_00389AC0.stream = 0;
    func_00292034(&parameters, 0, sizeof(parameters));
    parameters.entry = func_001DAA08;
    parameters.stack = D_00389E90;
    parameters.gp = D_00372DF0;
    parameters.stack_bytes = 0x1000;
    parameters.initial_priority = 2;
    D_00349F94 = func_002934A0(&parameters);
    func_00294260(D_00349F94, 0);
}
