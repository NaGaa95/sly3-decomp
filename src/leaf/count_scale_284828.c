// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char prefix[0x8C]; int group; float factor; };
struct Tracker { unsigned char prefix[0x14]; struct Slot *slot; };
int func_002852B0(struct Tracker *tracker);
int func_001C8768(void *object,int group);
int func_00284828(struct Tracker *tracker,void *object,int limit)
{
    int scaled;
    if(!func_002852B0(tracker))
        return limit;
    if(tracker->slot->group==-1)
        return limit;
    if(!func_001C8768(object,tracker->slot->group))
        return limit;
    scaled=(int)(tracker->slot->factor*(float)limit+0.5f);
    if(limit>0)
        return scaled<limit?scaled:limit;
    return 1;
}
