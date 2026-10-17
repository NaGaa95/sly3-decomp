// SLY3_CFLAGS: -Os -G0
struct Rec { int first; int second; void *third; int resolved; int word10; int word14; int word18; };
struct Group { struct Rec recs[6]; };
struct Holder { unsigned char prefix[0x270]; struct Group groups[2]; int counts[2]; };
extern unsigned char D_00475480[];
void *func_0017E1B8(void *game,int flags,int key,void *owner);
int func_0013B500(void *object,int kind);
void func_0023AAE8(void *object,void *receiver,int b,int c,void **output);
void *func_00292034(void *destination,int value,unsigned int length);
void func_002181D0(struct Holder *holder)
{
    int i,j,count;
    for(i=0;i<2;i++) {
        count=holder->counts[i];
        for(j=0;j<count;j++) {
            struct Rec *rec=&holder->groups[i].recs[j];
            void *object;
            if(rec->first!=-1) {
                object=func_0017E1B8(D_00475480,4,rec->first,holder);
                if(object && func_0013B500(object,0x2F)) {
                    rec->first=(int)object;
                    object=func_0017E1B8(D_00475480,4,rec->second,object);
                    if(object && func_0013B500(object,3)) {
                        rec->second=(int)object;
                        object=func_0017E1B8(D_00475480,4,(int)rec->third,(void *)rec->first);
                        if(object && func_0013B500(object,0x84)) {
                            rec->third=0;
                            func_0023AAE8(object,(void *)rec->first,-1,0,&rec->third);
                            if(rec->third) {
                                rec->resolved=1;
                                continue;
                            }
                        }
                    }
                }
            }
            func_00292034(rec,0,sizeof(struct Rec));
        }
    }
}
