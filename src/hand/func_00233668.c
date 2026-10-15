// Select the actual original word based on signed position/limit and ordered positive direction. Receiver is the sole input; nominal returned-word meaning remains provisional.
// Reference compiler shape: src/hand/func_001ACC80.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x15C]; int negative; int positive; int before; char unknown_168[0x8]; int limit; int position; char unknown_178[0x4]; float direction; };
int func_00233668(struct S *p){if(p->position<p->limit)return p->before;if(p->direction>0.0f)return p->positive;return p->negative;}
