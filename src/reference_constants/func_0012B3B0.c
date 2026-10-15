// Original USA entry 0x12b3b0; ordinary C reconstruction.
// Destination CRef A0 and source CRef A1 are retained across explicit source retain 12BB38 and destination release 12BC20; unsigned 16-bit tag and complete 32-bit payload are copied and destination pointer returned.
// SLY3_CFLAGS: -Os -G0
struct CRef  {
    unsigned short tag,padding;
    int payload;
};
void func_0012BB38(struct CRef *);
void func_0012BC20(struct CRef *);
struct CRef *func_0012B3B0(struct CRef *p,struct CRef *source)  {
    func_0012BB38(source);
    func_0012BC20(p);
    p->tag=source->tag;
    p->payload=source->payload;
    return p;
}
