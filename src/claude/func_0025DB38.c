// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Start a sound on an object (cf. Sly 2 src/hand/func_00210740.c).
struct VT { char pad[0x40]; short d; short pd; int (*kind)(void *); };
struct M { char pad[0xC]; struct VT *vt; };
struct O { char pad[0x112C]; int k; char pad2[0x11DC - 0x1130]; float f11DC; };
struct G { char pad[0x4F50]; float offset; };
struct O *func_0017E1B8(struct G *, int, int, void *);
int func_0013B500(struct O *, int);
struct M *func_002459F8(int);
void func_00244F08(struct M *, struct O *);
void func_00245100(struct M *, float, float);
void func_00244E08(struct M *, float);
void func_00244ED0(struct M *, float);
void func_00245130(struct M *, float);
void func_002BBCD8(struct M **, struct M *);
void func_0025DB38(float offset, float fade, float scale, struct G *p, int id, int oid, int x, int y, struct O *o, void *owner, void *unused, struct M **out)
{
    struct M *m;
    register struct O *r __asm__("$2") = o; /* pin: the looked-up object comes back in v0 */
    if (id == -1)
        return;
    __asm__ __volatile__("" ::: "$4"); /* zero-insn: keeps the a0 setup in the branch delay slot (as in Sly 2) */
    if (oid != -1)
        r = func_0017E1B8(p, 4, oid, owner);
    o = r;
    __asm__("" : "+r"(o)); /* zero-insn: o is used from its s-register copy */
    if (o && func_0013B500(o, 0x3A)) {
        offset += o->f11DC;
        if (o->k == 14 || o->k == 16)
            offset += 1.0f;
    }
    offset += p->offset;
    m = func_002459F8(id);
    func_00244F08(m, o);
    func_00245100(m, (float)x, (float)y);
    func_00244E08(m, scale);
    func_00244ED0(m, offset);
    func_00245130(m, fade);
    if (m->vt->kind((char *)m + m->vt->d) == 2)
        func_002BBCD8(out, m);
}
