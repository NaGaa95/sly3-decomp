// SLY3_CFLAGS: -Os -G0
struct Registry { unsigned char prefix[0x44]; int words[5]; int count; };
int func_0021A710(struct Registry *registry);
int func_0021A720(struct Registry *registry);
int func_0021A4E8(struct Registry *registry,int key)
{
    if(!func_0021A710(registry))
        return 0;
    if(func_0021A720(registry)!=1)
        return 0;
    {
        int count=registry->count;
        int found=0;
        int i;
        for(i=0;i<count;i++) {
            if(key==registry->words[i]) {
                found=1;
                break;
            }
        }
        return found;
    }
}
