// Original controller mode negotiation. Canonical SDK identities are retained.
// The complete receiver and downstream argument contracts are independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_mode.h"
extern "C" int func_002A1980(int,int);
extern "C" int func_002A1C78(int,int,int,int);
extern "C" int func_002A1DB0(int,int,int,int);
extern "C" int func_002A1B50(int,int,int,int);
extern "C" int func_002A1F28(int,int,const unsigned char *);
extern "C" int func_002A2168(int,int);
extern "C" int func_002A21C8(int,int);
extern "C" int func_002A1AF8(int,int);
extern "C" int func_001A8B88(INPUT_CONTROLLER *);
extern "C" int func_00210DE0(void *);
extern "C" void func_00210A90(void *);
extern "C" void func_001A7D80(INPUT_CONTROLLER *input) {
    int ready=0;
    if(!input->mode1050)return;
    int state=func_002A1980(input->port1044,input->slot1048);
    if(state==6||state==2)ready=1;
    if(input->mode1050!=3&&input->version1054&&D_0036BBD8.value-input->time1058>=2.0f)state=0;
    if(input->version1054&&!state)func_001A8780(input,1,0);
    if(!ready)return;
    int mode=input->mode1050;
    int version=input->version1054;
    switch(mode) {
    case 1:
        switch(version) {
        case 0: {
            int kind=func_002A1C78(input->port1044,input->slot1048,1,0);
            if(kind) {
                int extended=func_002A1C78(input->port1044,input->slot1048,2,0);
                if(extended>0)kind=extended;
                if(kind==4||kind==7) { version=1;mode=extended?1:3; }
            }
            break;
        }
        case 1: {
            int response=func_002A1DB0(input->port1044,input->slot1048,1,3);
            mode=response==1?2:1;
            break;
        }
        case 2: {
            int count=func_002A1B50(input->port1044,input->slot1048,-1,0);
            if(count!=2 ||
               func_002A1B50(input->port1044,input->slot1048,0,1)!=1 ||
               func_002A1B50(input->port1044,input->slot1048,0,2)!=2 ||
               func_002A1B50(input->port1044,input->slot1048,0,3)!=0 ||
               func_002A1B50(input->port1044,input->slot1048,1,1)!=1 ||
               func_002A1B50(input->port1044,input->slot1048,1,2)!=1 ||
               func_002A1B50(input->port1044,input->slot1048,1,3)!=1)mode=3;
            else {
                unsigned char alignment[6];
                memset(alignment,0xFF,sizeof(alignment));
                for(int i=0;i<count;++i)alignment[i]=i;
                if(func_002A1F28(input->port1044,input->slot1048,alignment)==1)mode=2;
            }
            break;
        }
        case 3:
            if(func_002A2168(input->port1044,input->slot1048)!=1)mode=3;
            else if(func_002A21C8(input->port1044,input->slot1048)==1)mode=2;
            break;
        }
        break;
    case 2:
        switch(func_002A1AF8(input->port1044,input->slot1048)) {
        case 0:
            switch(input->version1054) {
            case 1:version=2;mode=1;break;
            case 2:version=3;mode=1;break;
            case 3:version=4;mode=3;break;
            default:version=0;break;
            }
            break;
        case 1:mode=1;break;
        case 2:break;
        default:version=0;break;
        }
        break;
    case 3:
        if(func_001A8B88(input)) {
            if(input->version1054>=3) {
                void *callback=input->callback1124;
                if(func_00210DE0(callback))func_00210A90(callback);
            }
        } else { mode=1;version=0; }
        break;
    }
    func_001A8780(input,mode,version);
}
