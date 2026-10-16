// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Record;
struct State;
struct RequestRecord64;
struct RequestGame;
struct SequenceCommand {
    unsigned int kind;
    const struct Record *movie_record;
    const struct RequestRecord64 *request;
    int word;
    int flags;
    const struct RequestRecord64 *fallback_request;
    int identifier;
};
struct SequenceRuntime {
    int count;
    struct SequenceCommand commands[16];
    int cursor;
};
struct MovieSequenceView { char prefix[0x108]; int active; };
struct MenuSequenceView { char prefix[0x58]; int mode; };
extern unsigned char D_00389AC0[], D_00475480[], D_003751D0[], D_0036C700[];
extern struct RequestRecord64 D_00345820;
extern int func_001C6F20(void *);
extern void func_001DBD08(struct State *, const struct Record *);
extern void func_00289070(struct RequestGame *, const struct RequestRecord64 *, int, int, int);
extern void func_00189E70(void *, const struct RequestRecord64 *, int, int);
extern void func_001D0D30(void *, int);

void func_001C6F30(void *receiver)
{
    struct SequenceRuntime *runtime = receiver;
    struct SequenceCommand *command;
    struct MovieSequenceView *movie;
    if (!func_001C6F20(runtime))
        return;
    command = &runtime->commands[runtime->cursor++];
redispatch:
    switch (command->kind) {
    case 0:
    case 1:
        movie = (struct MovieSequenceView *)D_00389AC0;
        func_001DBD08((struct State *)movie, command->movie_record);
        if (command->kind == 1)
            movie->active = command->kind;
        func_00289070((struct RequestGame *)D_00475480, &D_00345820, 0x1A8, 0, -1);
        break;
    case 2:
        func_00289070((struct RequestGame *)D_00475480, command->request,
                     command->word, command->flags, -1);
        break;
    case 3:
        func_00189E70(D_0036C700, command->fallback_request, command->identifier, 2);
        break;
    case 4:
        command = &runtime->commands[runtime->cursor-- - 2];
        goto redispatch;
    case 5:
        if (!((struct MenuSequenceView *)D_003751D0)->mode)
            func_001D0D30(D_003751D0, 1);
        func_001C6F30(runtime);
        break;
    }
}
