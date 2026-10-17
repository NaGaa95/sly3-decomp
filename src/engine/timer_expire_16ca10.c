// SLY3_CFLAGS: -Os -G0
struct ExpireGame { unsigned char prefix[0x3EB8]; int count; void *items[1]; };
struct ExpireSelf { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x34 - 0x14]; float first; float second; unsigned char gap3C[0x44 - 0x3C]; int state; };
extern float D_0036BB98;
extern const float D_00321020[];
extern struct ExpireGame D_00475480;
void func_002389A0(void *self);
int func_00238AD0(void *self);
void func_0016CB38(void *self, int mode);
void func_00167D38(void *item, int mode);
void func_00241150(void *owner, int mode);
void func_0016CA10(struct ExpireSelf *self)
{
    int previous;
    float now;
    func_002389A0(self);
    do {
        previous = self->state;
        if(previous == 0) {
            if(func_00238AD0(self)) func_0016CB38(self, -1);
        }
    } while(self->state != previous);
    if(self->state == 0) {
        now = D_0036BB98;
        if(self->first < now + 0.0001f) {
            int i;
            self->first = D_00321020[0];
            for(i = 0; i < D_00475480.count; i++) func_00167D38(D_00475480.items[i], 0);
        }
        if(self->second < now + 0.0001f) {
            self->second = D_00321020[0];
            func_00241150(self->owner, 2);
        }
    }
}
