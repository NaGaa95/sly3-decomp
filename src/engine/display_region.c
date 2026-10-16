// SLY3_CFLAGS: -Os -G0
typedef int RegionWord;

typedef struct DisplayWidthPrefix {
    unsigned char unaccessed0[4];
    int selector;
} DisplayWidthPrefix;

typedef struct DisplayPackedRegionPrefix {
    unsigned char unaccessed0[0x18];
    RegionWord coordinates;
} DisplayPackedRegionPrefix;

int func_002BC640(void *unusedReceiver, int value);
unsigned int fptoui(float value);

void func_00196768(void *opaqueOwner, void *opaqueRegion, float x, float y)
{
    DisplayWidthPrefix *owner = opaqueOwner;
    DisplayPackedRegionPrefix *region = opaqueRegion;
    int width = func_002BC640(owner, owner->selector);
    int offset = width == 0x180 ? 0x2F0 : 0x27C;
    RegionWord coordinate;

    coordinate = (int)fptoui(x + (float)offset);
    region->coordinates = (region->coordinates & ~0xFFF) |
                          (coordinate & 0xFFF);
    coordinate = (int)fptoui(y + 50.0f);
    region->coordinates = (region->coordinates & (int)0xFF800FFFU) |
                          ((coordinate & 0x7FE) << 12);
}
