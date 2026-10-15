// SLY3_CFLAGS: -Os -G0
struct ChoiceActor {
    unsigned char opaque00[0x298];
    int fallback;
    unsigned char opaque29C[0x1520 - 0x29C];
    int state;
    unsigned char opaque1524[0x1540 - 0x1524];
    void *attachment;
    unsigned char opaque1544[0x1594 - 0x1544];
    int selected;
    unsigned char opaque1598[0x1874 - 0x1598];
    int condition;
    unsigned char opaque1878[0x1AA4 - 0x1878];
    int attached_choice;
};

struct ChoiceWords {
    unsigned char prefix[0x1A38];
    int words[0];
};
struct SelectedWords {
    unsigned char prefix[0x1A98];
    int words[0];
};

int func_001B5C78(void *context, int *mode);
void *func_001C4088(void *context, int *mode);
int func_001BD718(void *context, int *mode);
void func_0024DF48(void *receiver, int result, int mode);
int func_001530F8(void *receiver);

void func_001E0998(struct ChoiceActor *actor)
{
    int mode = 0;
    int result;
    switch (actor->state) {
    case -1:
        result = 0;
        break;
    case 14:
        result = func_001B5C78((char *)actor + 0x500, &mode);
        break;
    case 15:
        result = (int)func_001C4088((char *)actor + 0xE40, &mode);
        break;
    case 2:
        if (actor->attachment)
            result = actor->attached_choice;
        else
            result = func_001BD718((char *)actor + 0x320, &mode);
        break;
    case 5:
        result = ((struct SelectedWords *)actor)->words[actor->selected];
        break;
    default:
        result = ((struct ChoiceWords *)actor)->words[actor->state];
        break;
    }
    if (!result)
        result = actor->fallback;
    func_0024DF48(actor, result, mode);
}

int func_001E0A78(struct ChoiceActor *actor)
{
    int result = func_001530F8(actor);
    if (result != -1)
        return result;
    switch (actor->state) {
    case 1:
    case 13:
        return 1;
    case 5:
        if (actor->selected == 2)
            result = 1;
        return result;
    case 10:
        if (actor->condition)
            result = 1;
        return result;
    }
    return -1;
}

int func_001E0B10(struct ChoiceActor *actor)
{
    switch (actor->state) {
    case 0:
    case 1:
    case 10:
    case 11:
        return 1;
    }
    return 0;
}
