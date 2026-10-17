// SLY3_CFLAGS: -Os -G0
struct EventItem { unsigned char prefix[0x50]; int value; };
struct EventProvider { unsigned char prefix[0x14]; struct EventItem *item; };
struct EventSubject { unsigned char prefix[0xA8]; int slot; };
struct EventSelf { unsigned char prefix[0x54]; struct EventSubject *first; struct EventSubject *second; };
extern struct EventProvider D_004BC230;
extern unsigned char D_00475480[];
int func_00185FD8(void *self);
void func_00186DA0(void *self);
int func_002852B0(void *provider);
int func_002845B0(void *provider,void *subject,int mode);
void func_001871C0(void *self);
void func_0018AAE0(void *game,void *subject);
void func_00186810(struct EventSelf *self,struct EventSubject *subject)
{
    if(func_00185FD8(self)) {
        if(subject==self->first) func_00186DA0(self);
        if(func_002852B0(&D_004BC230)) {
            if(func_002845B0(&D_004BC230,subject,2)) func_001871C0(self);
        } else if(subject==self->second) {
            func_001871C0(self);
        }
        if(subject->slot!=-1) {
            int hit=0;
            if(!D_004BC230.item || D_004BC230.item->value==1) hit=1;
            if(hit) func_0018AAE0(D_00475480,subject);
        }
    }
}
