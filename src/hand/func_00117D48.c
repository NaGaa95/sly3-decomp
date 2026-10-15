// Actual CSwHeap interface: receiver and allocationKind are unused by this body.
// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct MSG {
    int n;
    int nKind;
}
MSG;
void *func_001D25B0(MSG *pmsg);
void *func_00117D48(void *pv, int n, int allocationKind) {
    MSG msg;
    msg.n = n;
    msg.nKind = 0x10;
    return func_001D25B0(&msg);
}
