// SLY3_CFLAGS: -Os -G0
void func_00154750(void *p);
int func_00154798(void *p, int kind);
void func_0013E510(void *p, int n);

void func_00140438(char *p)
{
    func_00154750(p);
    if (*(int *)(p + 0x1520) == 0xE && *(int *)(p + 0x1294) >= 4 && *(int *)(p + 0x1294) < 7) {
        int kind = *(int *)(*(char **)(p + 0x12A0) + 0x13C);
        switch (kind) {
        case 6: case 8: case 10: case 13: case 15: case 16:
            if (!func_00154798(p, kind))
                func_0013E510(p, 0);
            break;
        }
    }
}
