// SLY3_CFLAGS: -Os -G0
int func_00156388(char *p)
{

    if (*(int *)(p + 0x214))
        return 0;

    switch (*(int *)(p + 0x508)) {
    case 3: case 4:
        return 4;
    }
    if (*(int *)(p + 0x33C) != -1)
        return 1;
    switch (*(int *)(p + 0xE44)) {
    default:
        return 0;
    case 4: case 8: case 9: case 13:
        return 1;
    case 7:
        return 7;
    case -1: case 0: case 6:
        break;
    }
    {
        int s = *(int *)(p + 0x10D4);
        if ((s == 0 || s == 2) && (*(int *)(*(char **)(p + 0x10DC) + 0x50) & 0x20000))
            return 1;
    }
    return 7;
}
