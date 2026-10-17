// SLY3_CFLAGS: -Os -G0
#include "range_context_api.h"
struct ScreenExtent { unsigned char prefix[0x1C]; int unit; int base; };
extern struct ScreenExtent D_0036DBE0;
struct Rect { int left, top, right, bottom; };
struct Sprite {
    unsigned char prefix[0x160];
    struct Rect rect;
    unsigned char gap170[0x454 - 0x170];
    int handle, offset, size, scale;
};
struct Holder {
    unsigned char prefix[0x3EB8];
    int count;
    struct Sprite *sprites[1];
};
int func_0013B500(void *object,int kind);
void func_0027DC08(int width,int height,int *scale,int *size);
int func_00196C18(void *context,int size);
void func_0027DD40(struct Holder *holder)
{
    ZPR context;
    int i;
    if(!*(int *)((char *)holder+0x3EFC)) return;
    *(int *)((char *)holder+0x3EFC)=0;
    func_00196AA8(&context,2*D_0036DBE0.unit+D_0036DBE0.base,3*D_0036DBE0.unit);
    for(i=0;i<holder->count;i++) {
        struct Sprite *sprite=holder->sprites[i];
        if(func_0013B500(sprite,6)) {
            struct Rect *rect=&sprite->rect;
            func_0027DC08(rect->right-rect->left,rect->bottom-rect->top,&sprite->scale,&sprite->size);
            sprite->handle=func_00196C18(&context,sprite->size);
            sprite->offset=(context.limitWord-sprite->size)&-0x20;
        }
    }
}
