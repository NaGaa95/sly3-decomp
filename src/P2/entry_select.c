// SLY3_CFLAGS: -Os -G0
struct Entry { int key; unsigned char gap4[0x18]; };
struct Group { struct Entry entries[6]; };
struct Manager { unsigned char prefix[0x270]; struct Group groups[2]; int counts[2]; };
void func_002183F8(struct Manager *manager,struct Entry *entry,int group,int flags);
void func_00218358(struct Manager *manager,int key)
{
    if(key) {
        struct Entry *found=0;
        int group;
        int g;
        for(g=0;g<2;g++) {
            int count=manager->counts[g];
            int i;
            for(i=0;i<count;i++) {
                struct Entry *entry=&manager->groups[g].entries[i];
                if(entry->key==key) {
                    found=entry;
                    group=g;
                }
            }
        }
        if(found)
            func_002183F8(manager,found,group,0);
    }
}
