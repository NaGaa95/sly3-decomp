// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
int func_002954A0(char **cursor, int *remaining, int character)
{
    char *p;
    if (*remaining == 0)
        return 1;
    if (character >= 256) {
        **cursor = 0;
        return 0;
    }
    if (*remaining == 1)
        character = 0;
    p = *cursor;
    *p++ = character;
    *cursor = p;
    (*remaining)--;
    return 1;
}
