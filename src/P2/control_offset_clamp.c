// SLY3_CFLAGS: -Os -G0
struct ControlOffsets { char unknown_0[0x190]; int first; int second; int first_limit; int second_limit; int third; int fourth; };
static inline int Minimum(int value,int limit){return value<limit?value:limit;}
void func_00217F68(void *control,int axis);
void func_00215808(struct ControlOffsets *control,int third,int fourth)
{
    control->third=Minimum(third,control->first_limit);
    control->fourth=Minimum(fourth,control->second_limit);
    func_00217F68(control,0);
    func_00217F68(control,1);
}
