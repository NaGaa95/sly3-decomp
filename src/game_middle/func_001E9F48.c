// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ModeActor {
    unsigned char prefix[0x1470];
    int state;
};
void func_001E9BC8(void *actor, int state);

/* Request-to-state mapping: select the actor state for one of the ten request codes. */
void func_001E9F48(struct ModeActor *actor, int request)
{
    switch (request) {
    case -1:
        func_001E9BC8(actor, -1);
        break;
    case 0:
        func_001E9BC8(actor, 0);
        break;
    case 1:
        func_001E9BC8(actor, 4);
        break;
    case 2:
        func_001E9BC8(actor, 5);
        break;
    case 3:
        func_001E9BC8(actor, 6);
        break;
    case 9:
        func_001E9BC8(actor, 7);
        break;
    case 5:
        func_001E9BC8(actor, 8);
        break;
    }
}

/* State-to-request mapping, the inverse of the function above. */
int func_001E9FF0(struct ModeActor *actor)
{
    switch (actor->state) {
    case -1:
        return -1;
    case 0:
        return 0;
    case 4:
        return 1;
    case 5:
        return 2;
    case 6:
        return 3;
    case 7:
        return 9;
    case 8:
        return 5;
    default:
        return 11;
    }
}
