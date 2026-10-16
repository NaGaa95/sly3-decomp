// SLY3_CFLAGS: -Os -G0 -ffast-math
typedef int WindowPacked __attribute__((mode(TI)));
struct WindowInterval { float start, end; };
struct WindowEntry { int unused0, unused4; struct WindowInterval *interval; };
struct WindowMatrix { unsigned char prefix[0x30]; WindowPacked position; };
struct WindowVirtualEntry { short adjustment, reserved; void *function; };
struct WindowPositionOwner { unsigned char prefix[0xC]; struct WindowVirtualEntry *table; };
struct WindowController {
    unsigned char prefix[0x18];
    struct WindowPositionOwner *positionOwner;
    float time;
};
struct WindowDefinition {
    unsigned char prefix[0x40];
    struct WindowController *controller;
    unsigned char toPeriod[0x64 - 0x44];
    float period;
    unsigned char toEntries[0xC0 - 0x68];
    struct WindowEntry *entries;
};
struct WindowState {
    int unused;
    struct WindowDefinition *definition;
    unsigned char toFraction[0x50 - 8];
    float fraction;
    unsigned char toSound[0x90 - 0x54];
    int sound;
    float lowGain, highGain;
    int outside[2];
};
float func_0011EDB8(float, float);
void *func_002459F8(int);
void func_00244F08(void *, int);
void func_00245000(void *, WindowPacked);
void func_00245100(void *, float, float);
void func_00244E08(void *, float);

void func_00258DA0(struct WindowState *state)
{
    struct WindowController *controller = state->definition->controller;
    float time = controller->time;
    int first = 1;
    int i;
    for (i = 0; i < 2; ++i) {
        struct WindowDefinition *definition = state->definition;
        struct WindowInterval *interval = definition->entries[i].interval;
        int outside = interval->end <=
            func_0011EDB8(time - interval->start, definition->period);
        if (outside == state->outside[i])
            continue;
        if (!outside && first) {
            float gain = state->fraction;
            void *voice;
            struct WindowPositionOwner *owner;
            struct WindowVirtualEntry *entry;
            struct WindowMatrix *matrix;
            first = 0;
            {
                float complement = 1.0f - gain;
                gain *= state->highGain;
                gain += complement * state->lowGain;
            }
            voice = func_002459F8(state->sound);
            func_00244F08(voice, 0);
            owner = controller->positionOwner;
            entry = owner->table + 36;
            matrix = ((struct WindowMatrix *(*)(void *))entry->function)
                ((char *)owner + entry->adjustment);
            func_00245000(voice, matrix->position);
            func_00245100(voice, 500.0f, 2000.0f);
            func_00244E08(voice, gain);
        }
        state->outside[i] = outside;
    }
}
