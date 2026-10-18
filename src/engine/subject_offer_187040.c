// SLY3_CFLAGS: -Os -G0
struct OfferSubject {
    unsigned char prefix[0x40]; int kind;
    unsigned char gap44[0xB8-0x44]; int state;
};
struct OfferApplication;
struct OfferRecord;
struct OfferGame { unsigned char prefix[0x4050]; struct OfferSubject *offered; };
extern struct OfferApplication D_004BC230;
extern struct OfferGame D_00475480;
extern unsigned char D_00468D30[];
int func_002852B0(struct OfferApplication *application);
void func_00283F70(struct OfferApplication *application);
int func_0025AE28(struct OfferGame *game);
struct OfferRecord *func_0025E070(int index);
int func_0025E188(void);
void func_00289070(struct OfferGame *game,struct OfferRecord *record,int kind,void *owner,int index);
void func_00289198(struct OfferGame *game,int selection,int zero,void *context);
void func_001878E0(struct OfferSubject *self,int state);
void func_00187040(struct OfferSubject *self)
{
    if(self->state) return;
    if(func_002852B0(&D_004BC230)) {
        func_00283F70(&D_004BC230);
    } else {
        D_00475480.offered=self;
        if(!func_0025AE28(&D_00475480)) {
            if(self->kind==2)
                func_00289070(&D_00475480,func_0025E070(0),0x1A8,0,-1);
            else
                func_00289198(&D_00475480,func_0025E188(),0,D_00468D30);
        }
        func_001878E0(self,8);
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char KindOffset[(MEMBER_OFFSET(struct OfferSubject,kind)==0x40)?1:-1];
typedef char StateOffset[(MEMBER_OFFSET(struct OfferSubject,state)==0xB8)?1:-1];
typedef char OfferedOffset[(MEMBER_OFFSET(struct OfferGame,offered)==0x4050)?1:-1];
