// Original actor state predicates; each uses only its receiver.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ActorState1520 { char opaque[0x1520]; int state1520; };
struct ActorState19E0 { char opaque[0x19E0]; int state19E0; };
struct ActorState1470 { char opaque[0x1470]; int state1470; };
typedef char CheckState1520[(sizeof(struct ActorState1520) == 0x1524) ? 1 : -1];
typedef char CheckState19E0[(sizeof(struct ActorState19E0) == 0x19E4) ? 1 : -1];
typedef char CheckState1470[(sizeof(struct ActorState1470) == 0x1474) ? 1 : -1];

int func_0013F1B8(const struct ActorState1520 *receiver)
{
    return receiver->state1520 == 1;
}

int func_001AF298(const struct ActorState19E0 *receiver)
{
    return receiver->state19E0 == 2;
}

int func_001E0988(const struct ActorState1520 *receiver)
{
    return receiver->state1520 == 1;
}

int func_001EA060(const struct ActorState1470 *receiver)
{
    return receiver->state1470 == 1;
}

int func_001F0E28(const struct ActorState1470 *receiver)
{
    return receiver->state1470 == 1;
}

int func_0022D018(const struct ActorState1470 *receiver)
{
    return receiver->state1470 == 1;
}
