// When the actual receiver condition permits it, initialize all six packet bytes, narrow both original integer inputs to bytes0/1 and submit them with the original two port/slot indices. Every consumed direct input is explicit.
// Reference compiler shape: src/hand/func_00149A50.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S {int port,slot;};
int func_00210DE0(void *receiver);
void *func_00292034(void *destination,int value,unsigned int count);
int func_002A1E68(int port,int slot,const unsigned char *packet);
void func_00210D78(struct S *p,int first,int second){if(func_00210DE0(p)){unsigned char packet[6];func_00292034(packet,0,6);packet[0]=first;packet[1]=second;func_002A1E68(p->port,p->slot,packet);}}
