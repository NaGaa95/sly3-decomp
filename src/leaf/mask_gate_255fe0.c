// SLY3_CFLAGS: -Os -G0
struct Mask { unsigned int words[4]; };
struct Receiver { unsigned char prefix[0x2F0]; int mode; struct Mask mask; };
extern struct Receiver *D_0036B334;
int func_002533C0(struct Receiver *receiver,int index);
int func_0013B500(void *object,int kind);
int func_00255D78(struct Receiver *receiver,void *other,const struct Mask *mask);
int func_00255FE0(struct Receiver *receiver,void *other,struct Mask mask)
{
    if(func_002533C0(receiver,0x2A))
        return 1;
    if(func_0013B500(other,0x35)&&receiver->mode!=1&&receiver->mode!=2&&receiver!=D_0036B334)
        return 1;
    return func_00255D78(receiver,other,&mask);
}
