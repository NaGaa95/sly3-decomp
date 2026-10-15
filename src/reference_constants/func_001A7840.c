// Original USA entry 0x1a7840; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Player  {
    char storage[0x11C0];
};
extern struct Player D_0036E740[];
void func_001A7CE0(struct Player *);
void func_001A7840(void)  {
    unsigned int i;
    for(i=0;i<2;++i)func_001A7CE0(&D_0036E740[i]);
}
