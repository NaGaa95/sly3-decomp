// SLY3_CFLAGS: -Os -G0
typedef struct DisplayCoordinatePrefix {
    unsigned char unaccessed0[0x24];
    float x;
    float y;
} DisplayCoordinatePrefix;

void func_00196768(void *owner, void *record, float x, float y);
void func_00196880(void *owner, float x, float y);

void func_00196818(void *owner, float x, float y)
{
    func_00196880(owner, x, y);
    func_00196768(owner, (unsigned char *)owner + 0x58, x, y);
    func_00196768(owner, (unsigned char *)owner + 0x80, x, y);
}

void func_00196880(void *owner, float x, float y)
{
    DisplayCoordinatePrefix *display = owner;

    display->x = x;
    display->y = y;
}
