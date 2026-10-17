// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Owner { unsigned char prefix[0x50C]; int active; unsigned char gap510[0xC44]; float stamp; unsigned char gap1158[0x318]; int enabled; };
struct Record { unsigned char prefix[0x30]; float first; float second; unsigned char gap38[0x38]; int mode; void *table; };
extern float D_0036BB98;
extern char D_00349670[];
void func_00153D40(struct Owner *owner, struct Record *record);
void func_0022D370(struct Owner *owner, struct Record *record)
{
    if(owner->enabled && owner->active)
        owner->stamp=D_0036BB98;
    func_00153D40(owner, record);
    record->table=D_00349670;
    record->mode=4;
    record->first=-0.1f;
    record->second=-120.0f;
}
