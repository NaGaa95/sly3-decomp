// SLY3_CFLAGS: -Os -G0
struct Binding { unsigned char prefix[0xA0]; int kindA0; unsigned char gapA4[0x1C]; int kindC0; };
struct Chained { unsigned char prefix[0x10]; struct Chained *owner; unsigned char gap14[0xC4]; struct Binding *binding; unsigned char gapDC[0x4C]; unsigned long state; };
struct Chained *func_0023B650(struct Chained *object)
{
    struct Chained *last=0;
    struct Chained *next=object;
    while(next) {
        struct Binding *binding;
        last=next;
        binding=last->binding;
        if(binding) {
            if(binding->kindC0!=3)
                break;
            if(binding->kindA0!=binding->kindC0)
                break;
        }
        if(last->state&4)
            break;
        next=last->owner;
    }
    return last;
}
