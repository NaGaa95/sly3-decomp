// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct O { char pad[0x60]; int id; };
void func_00244CA8(struct O *p, float f);
void func_002BBCD8(struct O **pp, int a);
void func_0025DCA8(void *a, int id, void *b, struct O **pp)
{
    struct O *p = *pp;
    if (!p)
        return;
    if (id != -1 && p->id != id)
        return;
    func_00244CA8(p, 0.0f);
    func_002BBCD8(pp, 0);
}
