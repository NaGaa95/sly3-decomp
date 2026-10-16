// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

extern const char D_0032B2E0[];
int func_00296B28(const char *path, int flags, ...);
int func_00296F38(int descriptor, void *buffer, int count);
int func_00296DB8(int descriptor);
int atoi(const char *text);

int func_0029F1C0(void)
{
    char buffer[256];
    char *cursor;
    unsigned int count;
    int descriptor = func_00296B28(D_0032B2E0, 1);

    if (descriptor < 0)
        return -1;
    count = 0;
    cursor = buffer;
    while (count < 256) {
        func_00296F38(descriptor, cursor, 1);
        if (*cursor++ == 0)
            break;
        ++count;
    }
    func_00296DB8(descriptor);
    return atoi(buffer + ((int)count - 9)) > 20010608;
}

typedef char RuntimeModelVersionWidths[
    (sizeof(char) == 1 && (char)-1 < 0 && sizeof(int) == 4 &&
     sizeof(void *) == 4) ? 1 : -1];
