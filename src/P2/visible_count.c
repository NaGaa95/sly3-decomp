// SLY3_CFLAGS: -Os -G0
struct Child { unsigned char prefix[0x518]; int hidden; };
struct Group { unsigned char prefix[0x40]; struct Child *selected; struct Child *children[1]; };
struct GroupCount { unsigned char prefix[0x58]; int count; };
int func_0021A720(struct Group *group)
{
    int total=0;
    int i;
    for(i=0;i<((struct GroupCount *)group)->count;i++) {
        struct Child *child=group->children[i];
        if(child==group->selected && !*(int *)((char *)group+0xAC))
            continue;
        if(!child->hidden)
            total++;
    }
    return total;
}
