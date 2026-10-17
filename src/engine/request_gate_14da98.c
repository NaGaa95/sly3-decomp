// SLY3_CFLAGS: -Os -G0
struct Request { unsigned char prefix[0x50]; unsigned int flags; };
struct Owner { unsigned char prefix[0x164]; int state; };
void func_0014DC98(void *owner, int value);
int func_0014DA98(struct Owner *owner, struct Request *request)
{
    if(!(request->flags & 2) || owner->state != 5) return 0;
    func_0014DC98(owner, 0);
    return 1;
}
