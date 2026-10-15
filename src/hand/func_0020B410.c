// Restore the original saved basis and scalar, set the actual pending flag and remove the record from its pending list.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Record {
    QWORD basis[3];
    float value;
};
struct Receiver {
    char prefix[0xDC];
    struct Record *record;
    char middle[0x60];
    QWORD saved[3];
    float value;
};
extern int D_004798E8;
void func_0023DCF0(void *receiver);
void func_0020B410(struct Receiver *p) {
    p->record->basis[0] = p->saved[0];
    p->record->basis[1] = p->saved[1];
    p->record->basis[2] = p->saved[2];
    p->record->value = p->value;
    D_004798E8 = 1;
    func_0023DCF0(p);
}
