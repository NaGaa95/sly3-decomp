// Update two embedded actor records and apply the original owner event fallback.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#define Word(p, offset) (*(int *)((char *)(p) + (offset)))
#define Ptr(p, offset) (*(void **)((char *)(p) + (offset)))

void func_00155AF0(void *receiver);
// Actual independent argument banks: A0/A1/A2/A3, F12, then T0.
// The original forwards task in A3 although this setup body does not consume it.
void func_001AB308(void *receiver, void *channel, void *resource,
                  void *task, float gain, void *output);
int func_001AB560(void *receiver, void *record, void *task);
int func_00239A78(void *collection, int identifier);
void func_0023A070(void *owner, int identifier);

void func_001AB760(void *receiver)
{
    func_00155AF0(receiver);
    if (Ptr(receiver, 0x1AF8)) {
        void *first = (char *)receiver + 0x1650;
        void *second = (char *)receiver + 0x1750;
        float gain = 5.0f;

        func_001AB308(receiver, Ptr(receiver, 0x1AE0), Ptr(receiver, 0x1AE8),
                     Ptr(receiver, 0x1AF8), gain, first);
        func_001AB308(receiver, Ptr(receiver, 0x1ADC), Ptr(receiver, 0x1AE4),
                     Ptr(receiver, 0x1AFC), gain, second);
        if (!(func_001AB560(receiver, first, Ptr(receiver, 0x1AF8)) &&
              func_001AB560(receiver, second, Ptr(receiver, 0x1AFC))) &&
            !Word(receiver, 0x164C) && Ptr(receiver, 0x1140)) {
            void *owner = Ptr(receiver, 0x1140);
            if (func_00239A78(Ptr(owner, 0x24), 0x19A) >= 0)
                func_0023A070(Ptr(receiver, 0x1140), 0x19A);
            Word(receiver, 0x164C) = 1;
        }
    }
}
