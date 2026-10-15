// Sly 2 func_0015C198: submit a typed particle-emission packet.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ParticleWord __attribute__((mode(TI)));
struct ParticleCommand {
    int flags, owner_word;
    float first, second;
    ParticleWord vector, position;
    ParticleWord reserved;
};
struct ParticleEntry { short delta, reserved; void (*call)(void *, ParticleCommand *); };
struct ParticleReceiver { int prefix[3]; ParticleEntry *table; };
extern "C" void func_00179E58(ParticleReceiver *receiver, int flags, int owner_word,
    float first, float second, ParticleWord vector, ParticleWord position)
{
    ParticleCommand command;
    command.flags=flags;
    command.owner_word=owner_word;
    command.first=first;
    command.second=second;
    command.vector=vector;
    command.position=position;
    ParticleEntry *entry=&receiver->table[55];
    entry->call((char *)receiver+entry->delta,&command);
}

// Base emission method: the receiver and packet are intentionally ignored.
extern "C" void func_00179EA0(ParticleReceiver *, ParticleCommand *)
{
}
