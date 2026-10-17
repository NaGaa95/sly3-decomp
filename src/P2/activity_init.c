// SLY3_CFLAGS: -Os -G0
struct Range { unsigned low,high; };
struct Activity {
    struct Range first;
    unsigned char gap08[0x28];
    void *command;
    int field34,field38;
    struct Range second;
    const void *defaults;
    int field48;
    struct Range third;
    int field54,index,field5C;
    unsigned char gap60,flag61,gap62[2];
    int slot;
    int list;
};
extern char D_00317FC0[];
void func_0011AD68(int *list);
void func_002643F8(struct Activity *activity)
{
    activity->defaults=D_00317FC0;
    activity->command=0;
    activity->field54=0;
    activity->first.low=0x7F7F7F7F;
    activity->first.high=0xFFFFFFFF;
    activity->second.low=0x7F7F7F7F;
    activity->second.high=0xFFFFFFFF;
    activity->third.low=0x7F7F7F7F;
    activity->third.high=0xFFFFFFFF;
    activity->slot=-1;
    activity->index=0;
    activity->field34=0;
    activity->flag61=0;
    activity->field5C=0;
    activity->field38=0;
    activity->field48=0;
    func_0011AD68(&activity->list);
}
