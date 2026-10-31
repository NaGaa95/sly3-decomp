// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
// Actor state <-> command mapping: forward (state -> command id handed to func_0022CA70) and inverse (current mode -> id).
struct Actor { unsigned char pad00[0x1470]; int mode; };
void func_0022CA70(struct Actor *actor, int command);
void func_0022CF00(struct Actor *actor, int state)
{
    switch (state) {
    case -1: func_0022CA70(actor, -1); break;
    case 0: func_0022CA70(actor, 0); break;
    case 1: func_0022CA70(actor, 3); break;
    case 2: func_0022CA70(actor, 4); break;
    case 3: func_0022CA70(actor, 5); break;
    case 9: func_0022CA70(actor, 7); break;
    case 5: func_0022CA70(actor, 8); break;
    }
}
int func_0022CFA8(struct Actor *actor)
{
    switch (actor->mode) {
    case -1: return -1;
    case 0: return 0;
    case 3: return 1;
    case 4: return 2;
    case 5: return 3;
    case 7: return 9;
    case 8: return 5;
    default: return 0xB;
    }
}
