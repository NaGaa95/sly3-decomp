// SLY3_CFLAGS: -Os -G0
typedef struct ID_RECORD {
    char opaque0[8]; float value; char opaqueC[4]; int identifier;
} ID_RECORD;
typedef struct ACTIVITY_RECORD {
    char opaque0[8]; short index; char opaqueA[2]; float offset; char opaque10[8];
} ACTIVITY_RECORD;
typedef struct GAIN_GROUP {
    unsigned short idCount, activityCount;
    ID_RECORD *ids;
    ACTIVITY_RECORD *activities;
    char opaqueC[0x30-0xC];
} GAIN_GROUP;
typedef struct GAIN_GROUPS_VIEW {
    char opaque0[0x70]; unsigned short count; short padding;
    GAIN_GROUP *groups;
} GAIN_GROUPS_VIEW;
float func_002617F0(void *receiver, int identifier)
{
    GAIN_GROUPS_VIEW *p = (GAIN_GROUPS_VIEW *)receiver;
    int i, j;
    if (identifier == -1)
        return 0.0f;
    for (i = 0; i < p->count; i++) {
        GAIN_GROUP *group = &p->groups[i];
        for (j = 0; j < group->idCount; j++) {
            ID_RECORD *record = &group->ids[j];
            ACTIVITY_RECORD *selected = 0;
            if (identifier == record->identifier) {
                int k;
                for (k = 0; k < group->activityCount; k++) {
                    ACTIVITY_RECORD *item = &group->activities[k];
                    if (item->index != -1)
                        selected = item;
                }
                if (selected)
                    return record->value - selected->offset;
            }
        }
    }
    return 0.0f;
}
