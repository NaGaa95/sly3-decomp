// SLY3_CFLAGS: -Os -G0
struct ActorRequestEntry { int kind; void *resource; void *message; };
struct ActorRequestOwner;
struct ActorRequestEntry *func_001400C0(struct ActorRequestOwner *owner,int kind)
{
    switch(kind) {
    case 4: return (struct ActorRequestEntry *)((char *)owner+0x1950);
    case 6: return (struct ActorRequestEntry *)((char *)owner+0x195C);
    case 10: return (struct ActorRequestEntry *)((char *)owner+0x1968);
    case 16: return (struct ActorRequestEntry *)((char *)owner+0x1974);
    case 13: return (struct ActorRequestEntry *)((char *)owner+0x1980);
    case 8: return (struct ActorRequestEntry *)((char *)owner+0x1998);
    case 15: return (struct ActorRequestEntry *)((char *)owner+0x198C);
    default: return 0;
    }
}
