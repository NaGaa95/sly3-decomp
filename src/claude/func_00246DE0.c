// SLY3_CFLAGS: -Os -G0
// Attach an owner to a link record passed as a 64-bit value: clear the word before it, then store the owner.
typedef int S64 __attribute__((mode(DI)));
struct Link { char prefix[0x6C]; int a; void *ownerA; char gap[0xA0 - 0x74]; int b; void *ownerB; };
void func_00246DE0(void *owner, S64 x) { struct Link *l = (struct Link *)(int)x; l->a = 0; l->ownerA = owner; }
void func_00246DF8(void *owner, S64 x) { struct Link *l = (struct Link *)(int)x; l->b = 0; l->ownerB = owner; }
