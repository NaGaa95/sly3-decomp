// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Record { int fields[7]; } Record;
typedef struct State State;
struct FLOAT_PAIR { float first, second; };
void *memset(void *, int, unsigned int);
void func_001FD250(State *, const Record *);

void func_001FD2C0(State *state, const struct FLOAT_PAIR *pair)
{
    Record command;
    memset(&command, 0, sizeof(command));
    command.fields[1] = (int)pair->first;
    command.fields[2] = (int)pair->second;
    func_001FD250(state, &command);
}
