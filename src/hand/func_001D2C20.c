/* SLY3_CFLAGS: -Os -G0
 * Reset the accessed menu prefix after resolving its two opaque references.
 * This prefix describes accessed fields, not the object's allocation size.
 */
struct MenuPrefix {
    unsigned char unused0[0x30];
    void *first_reference;
    void *second_reference;
    unsigned char unused38[0x1FC - 0x38];
    int state;
    int selection;
};
typedef char MenuAccessedPrefixIs516Bytes[
    sizeof(struct MenuPrefix) == 0x204 ? 1 : -1
];
extern unsigned char D_00475480[];
void *func_0017E1B8(void *game, int flags, int key, void *owner);

void func_001D2C20(struct MenuPrefix *menu)
{
    void *game = D_00475480;
    menu->first_reference = func_0017E1B8(game, 0x405, 0x420, 0);
    menu->second_reference = func_0017E1B8(game, 0x405, 0x421, 0);
    menu->selection = -1;
    menu->state = 0;
}
