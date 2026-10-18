// SLY3_CFLAGS: -Os -G0
struct AppendState { char prefix[0x34]; int state; char gap38[0x58-0x38]; int count; int values[4]; float time; };
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
void func_0018C5A8(struct AppendState *owner,int value)
{
    switch(owner->state) {
    case 4: case 5:
        if(owner->count<4) {
            owner->values[owner->count++]=value;
            owner->time=D_0036BB98.now;
        }
        break;
    }
}
