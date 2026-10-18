// SLY3_CFLAGS: -Os -G0
struct NavigationChild { char prefix[0x130]; int mode; };
struct NavigationOwner {
    char prefix[0x198]; int mode;
    char gap19C[0x1A4-0x19C]; int count;
    struct NavigationChild *children[7]; int index;
    char gap1C8[0x1D4-0x1C8]; char request[0x10];
};
int func_001A99E0(void *request);
int func_001A9C38(void *request);
void *func_002459F8(int identifier);
void func_00244F08(void *sound, int flags);
void func_00171670(void *owner, int mode);
void func_00170F60(void *child, int mode);

void func_00171358(struct NavigationOwner *owner)
{
    int mode;
    do {
        mode=owner->mode;
        switch(mode) {
        case 0: {
            int horizontal=func_001A99E0(owner->request);
            int vertical=func_001A9C38(owner->request);
            if((horizontal<0 && owner->index<=0) ||
               (horizontal>0 && owner->index>=owner->count-1)) {
                func_00244F08(func_002459F8(0x36),0);
                break;
            }
            if(horizontal<0) {
                owner->index--;
                func_00171670(owner,2);
            } else if(horizontal>0) {
                owner->index++;
                func_00171670(owner,2);
            } else if(vertical>0) {
                func_00171670(owner,1);
                func_00170F60(owner->children[owner->index],0);
            } else if(vertical<0) {
                func_00171670(owner,1);
                func_00170F60(owner->children[owner->index],1);
            }
            break;
        }
        case 2:
            func_00171670(owner,0);
            break;
        case 1:
            if(owner->children[owner->index]->mode==3)
                func_00171670(owner,0);
            break;
        }
    } while(owner->mode!=mode);
}
