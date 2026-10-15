// Original USA entry 0x188420; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Object  {
    char pad[0x84];
    int local;
    struct Object **owner;
    char pad2[0xC0-0x8C];
    int state;
};
void func_00188420(struct Object *p)  {
    if(p->state==-1)  {
        if(!p->local)  {
            p->state=12;
            return;
        }
        p->state=(*p->owner)->state;
    }
}
