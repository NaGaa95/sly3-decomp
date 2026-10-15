// Accept the three original state/mode/active conditions, otherwise explicitly preserve original context A1 into156B98. Its complete conditional path uses that pointer for adjusted matrix callbacks, so receiver-only modeling is forbidden.
// Reference compiler shape: src/hand/func_0018F050.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x33C]; int mode; char unknown_340[0x1130]; int state; char unknown_1474[0x184]; int active; };
int func_00156B98(void *receiver,void *context);
int func_0022D4E8(struct S *p,void *context){if(p->state!=6&&p->mode!=0x11&&!p->active)return func_00156B98(p,context);return 1;}
