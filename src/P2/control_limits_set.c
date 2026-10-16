// SLY3_CFLAGS: -Os -G0
struct ControlLimits { char unknown_0[0x190]; int first; int second; int first_limit; int second_limit; int third; int fourth; };
static inline int Minimum(int value,int limit){return value<limit?value:limit;}
void func_00217F68(void *control,int axis);
void func_00215870(struct ControlLimits *control,int first_limit,int second_limit)
{
    control->first_limit=first_limit;
    control->second_limit=second_limit;
    control->first=Minimum(control->first,first_limit);
    control->second=Minimum(control->second,second_limit);
    control->third=Minimum(control->third,first_limit);
    control->fourth=Minimum(control->fourth,second_limit);
    func_00217F68(control,0);
    func_00217F68(control,1);
}
