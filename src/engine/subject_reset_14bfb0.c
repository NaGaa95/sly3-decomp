// SLY3_CFLAGS: -Os -G0
struct Subject {
    unsigned char prefix[0x3C]; unsigned int tag;
    unsigned char gap[0x130-0x40]; int state; float limit; float f138; float f13C; float f140;
    unsigned char gap2[0x148-0x144]; int f148;
    unsigned char gap3[0x1C4-0x14C]; int f1C4;
    unsigned char gap4[0x1D0-0x1C8]; int f1D0; int f1D4;
    unsigned char gap5[0x1E8-0x1D8]; void *self;
};
extern const float D_00320260;
void func_0023AE08(void *);
void func_0014BFB0(struct Subject *subject)
{
    unsigned int tag;
    func_0023AE08(subject);
    tag=subject->tag;
    subject->limit=D_00320260;
    subject->f140=subject->f13C=200.0f;
    subject->f1C4=1;
    subject->f148=-1;
    subject->f1D0=0x100;
    subject->f1D4=10;
    subject->state=0;
    if((tag^1)&1) *(unsigned int *)tag|=2;
    else subject->tag=tag|2;
    subject->self=subject;
}
