// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int Qword __attribute__((mode(TI)));
struct Eight { unsigned char bytes[8]; };
struct Object {
    unsigned char prefix[0x12C];
    int state;
    void *table;
    int slot;
    unsigned char gap138[0x18];
    Qword vector;
    struct Eight preserved;
    unsigned char gap168[0x34];
    int counter;
};
extern char D_0034A040[];
extern Qword D_003290B0;
extern struct Eight D_003290C0;
void func_0028FD70(struct Object *object);
void func_001C9118(struct Object *object, int mode);
void func_00273BB0(struct Object *object)
{
    func_0028FD70(object);
    object->slot=-1;
    object->vector=D_003290B0;
    object->preserved=D_003290C0;
    object->counter=0;
    object->state=7;
    object->table=D_0034A040;
    func_001C9118(object,1);
}
