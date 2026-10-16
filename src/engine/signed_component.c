// SLY3_CFLAGS: -Os -G0
int func_00175070(int value);
int func_00175008(int value)
{
    int group;
    if (value == -1)
        return -1;
    group = func_00175070(value);
    if (group == 0 || group == 9)
        return -1;
    return value % 16;
}
