// SLY3_CFLAGS: -Os -G0
struct FocusInit { unsigned char prefix[0x1498]; int firstId; int secondId; int thirdId; int fourthId; };
extern unsigned char D_00468D30[];
extern unsigned char D_00375290[];
extern unsigned char D_0036BD20[];
extern unsigned char D_004BC230[];
void *func_00292034(void *destination, int value, unsigned int bytes);
void func_0021D010(void *context, int flag);
void func_001CFDE8(void *object, int flag);
void func_00185638(void *self);
void func_00171A30(void *object);
void func_00284568(void *object);
void func_00184968(struct FocusInit *self)
{
    func_00292034(self, 0, 0x14A8);
    self->firstId = -1;
    self->secondId = -1;
    self->thirdId = -1;
    self->fourthId = -1;
    func_0021D010(D_00468D30, 0);
    func_001CFDE8(D_00375290, 0);
    func_00185638(self);
    func_00171A30(D_0036BD20);
    func_00284568(D_004BC230);
}
