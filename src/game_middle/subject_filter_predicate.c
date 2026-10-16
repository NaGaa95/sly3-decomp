// SLY3_CFLAGS: -Os -G0
struct KindFlags { unsigned char opaque[0x70]; unsigned long flags; };
struct SubjectInfo { unsigned char opaque[0xDC]; struct KindFlags *kind; };
struct Subject { unsigned char opaque00[4]; struct SubjectInfo *info; unsigned char opaque08[0x10]; unsigned long flags; };
struct Gate { unsigned char opaque[0x64]; int restricted; };
int func_0013B500(void *object, int identifier);
int func_001A3B28(struct Gate *gate, struct Subject *subject)
{
    if (subject->flags & 0x10000)
        return 0;
    if (subject->info->kind->flags & 4)
        return 0;
    if (gate->restricted) {
        if (func_0013B500(subject->info, 0x6F))
            return 0;
    }
    return !func_0013B500(subject->info, 0x31);
}
