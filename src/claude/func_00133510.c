extern struct CLOCK { float t; } g_clock;
void func_00133510(char *p, int s)
{
    if (*(int *)(p + 0xD8) != s) {
        *(int *)(p + 0xD8) = s;
        *(float *)(p + 0xDC) = g_clock.t;
    }
}
