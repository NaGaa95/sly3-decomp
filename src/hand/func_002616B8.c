// SLY3_CFLAGS: -Os -G0
#include "record_gain_types.h"
void func_002673D0(GAIN_GROUP *group, float gain);
void func_002673F8(GAIN_GROUP *group, int index, float gain, const void *context);

void func_002616B8(void *receiver, int identifier, float gain)
{
    GAIN_GROUPS_VIEW *p = (GAIN_GROUPS_VIEW *)receiver;
    int i, j;
    if (identifier == 0x37B) {
        func_002673D0(p->groups, gain);
        return;
    }
    for (i = 0; i < p->count; i++) {
        GAIN_GROUP *group = &p->groups[i];
        for (j = 0; j < group->idCount; j++) {
            ID_RECORD *record = &group->ids[j];
            int selected = -1;
            if (identifier == record->identifier) {
                int k;
                for (k = 0; k < group->activityCount; k++)
                    if (group->activities[k].index != -1)
                        selected = k;
                if (selected >= 0)
                    func_002673F8(group, selected, gain, 0);
            }
        }
    }
}
