// SLY3_CFLAGS: -Os -G0
struct FocusSlot { int first; int second; int third; int fourth; };
struct FocusClear {
    unsigned char prefix[0x10];
    int ids[2];
    struct FocusSlot slots[7];
    int grid[0x28][0x20];
    int word1488;
    int word148C;
    int word1490;
    int word1494;
};
void func_00185638(struct FocusClear *self)
{
    int i, j;
    unsigned int k;
    struct FocusSlot *slot;
    for(i = 0; i < 2; i++)
        self->ids[i] = -1;
    for(k = 0, slot = self->slots; k < 7; k++) {
        slot->first = 0;
        slot->second = 0;
        slot->third = -1;
        slot->fourth = -1;
        slot++;
    }
    for(j = 0; j < 0x28; j++)
        for(i = 0; i < 0x20; i++)
            self->grid[j][i] = 0;
    self->word1488 = -1;
    self->word148C = -1;
    self->word1490 = 0;
    self->word1494 = 0;
}
