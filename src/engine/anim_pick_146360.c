// SLY3_CFLAGS: -Os -G0

struct SelAnim { unsigned char prefix[0x60]; int id; };
struct SelOwner {
    unsigned char prefix[0x1E0]; float axisX; float axisY; unsigned char gap1E8[0x2B0 - 0x1E8]; int mode; unsigned char gap2B4[4]; int sub;
    unsigned char gap2BC[0x2F4 - 0x2BC]; int stage; unsigned char gap2F8[0x3D4 - 0x2F8];
    int id3D4, id3D8, id3DC, id3E0, id3E4, id3E8, id3EC, id3F0, id3F4; struct SelAnim *anim;
    unsigned char gap3FC[0x410 - 0x3FC]; int flag410; float time414; int flag418;
};
extern float D_0036BB98;
void func_00244CA8(float value);
void func_002BBCD8(struct SelAnim **slot, void *object);
void *func_002459F8(int id);
void func_00244F08(void *object, void *owner);
void func_00146360(struct SelOwner *self)
{
    int current, want;
    void *object;
    struct SelAnim **slot;
    current = -1;
    if(self->anim) current = self->anim->id;
    want = -1;
    switch(self->mode) {
    case 1:
        if((unsigned int)(self->sub - 1) < 2) want = self->id3F0;
        else if((unsigned int)(self->sub - 3) < 2) want = self->id3F0;
        else if(self->flag410) {
            if(D_0036BB98 - self->time414 < 1.5f) want = self->id3D8;
            else want = self->id3DC;
        } else if(self->flag418) want = self->id3E0;
        else {
            float ax = __builtin_fabsf(self->axisX);
            float ay = __builtin_fabsf(self->axisY);
            if(ax < 0.5f && ay < 0.2f) want = self->id3D4;
            else {
                float dy = ay - 0.2f;
                float dx = ax - 0.5f;
                if(dx < dy) {
                    if(self->axisY < 0.0f) { leaf3E8: want = self->id3E8; }
                    else goto leaf3EC;
                } else want = self->id3E4;
            }
        }
        break;
    case 3:
        if(self->stage == 0) goto leaf3E8;
        else if(self->stage == 2) { leaf3EC: want = self->id3EC; }
        break;
    case 4:
        want = self->id3F4;
        break;
    }
    if(want == current) return;
    slot = &self->anim;
    if(self->anim) {
        func_00244CA8(0.0f);
        func_002BBCD8(slot, 0);
    }
    if(want != -1) {
        object = func_002459F8(want);
        func_00244F08(object, self);
        func_002BBCD8(slot, object);
    }
}
