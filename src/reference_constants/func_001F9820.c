// Original USA entry 0x1f9820; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    float time;
    void *first,*second;
};
extern float D_0036BBD8;
extern int D_00467BE0;
extern struct Record *D_0036AEB0;
int func_002936C0(int);
void func_001F9820(struct Record *record,void *first,void *second)  {
    record->first=first;
    record->time=D_0036BBD8;
    record->second=second;
    D_0036AEB0=record;
    func_002936C0(D_00467BE0);
}
