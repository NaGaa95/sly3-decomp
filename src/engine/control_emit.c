// SLY3_CFLAGS: -Os -G0
typedef int ControlVector __attribute__((mode(TI)));
struct ControlMatrix { ControlVector rows[4]; };
struct ControlMatrixMethod {
    short delta, reserved;
    struct ControlMatrix *(*call)(void *);
};
struct ControlObject {
    unsigned char unaccessed00[0xC];
    struct ControlMatrixMethod *methods;
};
struct ControlEmitter {
    unsigned char unaccessed00[0x10];
    void *command_receiver;
    unsigned char unaccessed14[0x24];
    struct ControlObject *object;
};
extern ControlVector D_00317550;
void func_00240CB0(void *receiver, int option, void *owner, int flags,
                   int identifier, int active, ControlVector position,
                   ControlVector direction, void *output);

void func_00134AE0(struct ControlEmitter *receiver)
{
    struct ControlObject *object = receiver->object;
    struct ControlMatrixMethod *method = &object->methods[36];
    struct ControlMatrix *matrix = method->call((unsigned char *)object + method->delta);
    func_00240CB0(receiver->command_receiver, 0, receiver->object,
                  0x1000, 30, 0, matrix->rows[3], D_00317550, 0);
}
