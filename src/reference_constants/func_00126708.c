// Original USA entry 0x126708; ordinary C reconstruction.
// Original destination CRef A0 is retained. A real eight-byte local reference starts with signed tag-1;165B28 receives the actual475480 global and returns an object pointer.12B768 receives local reference/object,12AF00 receives destination/local source,12BC20 receives local for cleanup. All actual pointer inputs and returned destination are explicit.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
struct CRef  {
    short tag,padding;
    int payload;
};
extern char D_00475480[];
void *func_00165B28(void *);
void func_0012B768(struct CRef *,void *);
void func_0012AF00(struct CRef *,struct CRef *);
void func_0012BC20(struct CRef *);
struct CRef *func_00126708(struct CRef *ret)  {
    struct CRef ref;
    ref.tag=-1;
    func_0012B768(&ref,func_00165B28(D_00475480));
    func_0012AF00(ret,&ref);
    func_0012BC20(&ref);
    return ret;
}
