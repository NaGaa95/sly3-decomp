/* SLY3_CFLAGS: -Os -G0
 * Select a signed record ID from the original bounded nine-entry table.
 * The caller supplies menu in A0; the original body does not consume it.
 * The external mutable table is preserved original data, not emitted here.
 */
extern int D_00345F00[9];
int func_0025E188(void);
int func_0025E150(void);
int func_0025E160(int index);

int func_001D2E70(void *menu)
{
    int index = func_0025E188();
    if (index == 0)
        index = func_0025E160(func_0025E150());
    if ((unsigned int)index < 9)
        return D_00345F00[index];
    return -1;
}
