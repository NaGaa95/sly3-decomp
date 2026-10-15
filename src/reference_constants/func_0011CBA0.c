// Original USA entry 0x11cba0; ordinary C reconstruction.
// Destination matrix A0 and full128-bit direction A1 are actual inputs.11CBF0 consumes A0 destination plus two packed128-bit vectors in A1/A2, not a pointer in A1: the actual callee starts QMTC2 A1 and builds all three16-byte basis rows. The second vector is original317550; a real48-byte aligned local basis is copied to destination through complete memcpy291E8C, then destination is returned.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix  {
    qword rows[3];
};
extern qword D_00317550;
void func_0011CBF0(struct Matrix *,qword,qword);
void *func_00291E8C(void *,const void *,unsigned int);
struct Matrix *func_0011CBA0(struct Matrix *destination,qword direction)  {
    struct Matrix temporary;
    func_0011CBF0(&temporary,direction,D_00317550);
    func_00291E8C(destination,&temporary,sizeof(temporary));
    return destination;
}
