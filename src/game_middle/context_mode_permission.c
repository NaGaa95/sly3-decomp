// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ContextPermissionOwner {
    char prefix[0x13E0];
    int active;
};

struct ContextPermission {
    struct ContextPermissionOwner *owner;
    int word4;
    int state;
};

int func_001F4618(char *);

static __inline__ int HasActiveContextInput(struct ContextPermission *context)
{
    int result = 0;
    if (context->owner->active)
        result = func_001F4618((char *)context->owner) != 0;
    return result;
}

int func_001B5D08(void *receiver, int mode)
{
    struct ContextPermission *context = (struct ContextPermission *)receiver;
    if (mode == 3) {
        switch (context->state) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 13:
            return HasActiveContextInput(context);
        }
        return 0;
    }
    switch (context->state) {
    case 1:
    case 8:
    case 11:
    case 12:
        return 0;
    case 2:
        return mode != 2;
    case 3:
    case 4: {
        int permitted = 0;
        if (mode == 1 || mode == 2 || mode == 30)
            permitted = 1;
        return permitted;
    }
    }
    return 1;
}
