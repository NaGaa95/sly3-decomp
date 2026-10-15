// Apply the selected original word and actual mode; preserve unchecked state indexing.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

#define Word(p, offset) (*(int *)((char *)(p) + (offset)))

// GNU C storage view of the original indexed words, without a guessed capacity.
struct SelectionWords {
    char prefix[0x1850];
    int words[0];
};

int func_001B5C78(void *, int *);
void *func_001C4088(void *, int *);
int func_001BD718(void *, int *);
void func_0024DF48(void *, int, int);

void func_001ADBE0(void *receiver)
{
    int mode = 0;
    int result;
    int state = Word(receiver, 0x19E0);

    switch (state) {
    case -1:
        result = 0;
        break;
    case 8:
        result = func_001B5C78((char *)receiver + 0x500, &mode);
        break;
    case 5:
        result = (int)func_001C4088((char *)receiver + 0xE40, &mode);
        break;
    case 3:
        result = func_001BD718((char *)receiver + 0x320, &mode);
        break;
    case 17:
        result = Word(receiver, 0x560);
        break;
    default:
        result = ((struct SelectionWords *)receiver)->words[state];
        break;
    }

    if (!result) {
        result = Word(receiver, 0x1850);
    }
    func_0024DF48(receiver, result, mode);
}
