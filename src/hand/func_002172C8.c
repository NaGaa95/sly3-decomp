// Change the original enable word and restart only enabled state0/1 through explicit reset-1/state1 calls. Complete2171E8 consumes receiver/state only and generates its own vector/nullable outputs.
// Reference compiler shape: src/hand/func_001B4478.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x1C0]; int state; char unknown_1C4[0xA4]; int enabled; };
void func_002171E8(void *receiver,int state);
void func_002172C8(struct S *p,int enabled){if(p->enabled!=enabled){p->enabled=enabled;if(p->state<2){if(p->state<0)return;if(enabled){func_002171E8(p,-1);func_002171E8(p,1);}}}}
