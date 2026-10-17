// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ActionMask {
    unsigned char bytes[16];
    ActionMask() {}
    ActionMask(int index) asm("func_00252AD0");
    ActionMask operator|(const ActionMask &other) const {
        ActionMask result;
        for (int i = 0; i < 16; ++i)
            result.bytes[i] = bytes[i] | other.bytes[i];
        return result;
    }
};
struct ActionRecord { int word0; int word4; };
struct ActionPad {
    unsigned char prefix[0x1018];
    int word1018;
    unsigned char gap101C[0x1144 - 0x101C];
    unsigned int flags;
    unsigned char gap1148[0x11E4 - 0x1148];
    int word11E4;
};
extern "C" {
ActionRecord *func_00255130(ActionPad *pad, const ActionMask *mask);
}
extern "C" void func_00253AE0(ActionPad *pad)
{
    pad->flags = 0;
    pad->word11E4 = 0;
    {
        ActionMask mask(0xE);
        if (func_00255130(pad, &mask))
            pad->flags |= 2;
        else
            pad->word1018 = 2;
    }
    {
        ActionMask mask(0xD);
        if (func_00255130(pad, &mask))
            pad->flags |= 4;
    }
    {
        ActionMask mask(0x15);
        if (func_00255130(pad, &mask)) {
            pad->flags |= 1;
            ActionMask combined = ActionMask(0x15) | ActionMask(0x3D);
            pad->word11E4 = func_00255130(pad, &combined)->word4;
        }
    }
    {
        ActionMask mask(0x24);
        if (func_00255130(pad, &mask))
            pad->flags |= 8;
    }
    {
        ActionMask mask = ActionMask(0x41) | ActionMask(0x15);
        if (func_00255130(pad, &mask))
            pad->flags |= 0x10;
    }
    {
        ActionMask mask = ActionMask(0xC) | ActionMask(0xA);
        if (func_00255130(pad, &mask))
            pad->flags |= 0x20;
    }
    {
        ActionMask mask = ActionMask(0xC) | ActionMask(0xB);
        if (func_00255130(pad, &mask))
            pad->flags |= 0x40;
    }
    {
        ActionMask mask = ActionMask(0xC) | ActionMask(8);
        if (func_00255130(pad, &mask))
            pad->flags |= 0x80;
    }
    {
        ActionMask mask = ActionMask(0xC) | ActionMask(9);
        if (func_00255130(pad, &mask))
            pad->flags |= 0x100;
    }
}
