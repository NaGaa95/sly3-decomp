// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Record { int fields[7]; } Record;
typedef struct State State;
typedef struct PairWords { int first, second; } PairWords;
union QUEUE_COMMAND {
    Record record;
    struct {
        int operation;
        PairWords pair;
        float amount;
        int reserved10[3];
    } pair_amount;
    struct {
        int operation;
        int key;
        float values[4];
        int reserved18;
    } key_values;
};
extern const Record D_003255A8;
extern const Record D_003255C8;
extern const Record D_003255E8;
extern const Record D_00325608;
void func_001FD250(State *, const Record *);

void func_001FD320(State *state, const PairWords *pair, float amount)
{
    union QUEUE_COMMAND command;
    command.record = D_003255A8;
    command.pair_amount.pair = *pair;
    command.pair_amount.amount = amount;
    func_001FD250(state, &command.record);
}

void func_001FD390(State *state, int key,
                  float first, float second, float third, float fourth)
{
    union QUEUE_COMMAND command;
    command.record = D_003255C8;
    command.key_values.key = key;
    command.key_values.values[0] = first;
    command.key_values.values[1] = second;
    command.key_values.values[2] = third;
    command.key_values.values[3] = fourth;
    func_001FD250(state, &command.record);
}

void func_001FD400(State *state)
{
    Record command = D_003255E8;
    func_001FD250(state, &command);
}

void func_001FD460(State *state, const PairWords *pair)
{
    union QUEUE_COMMAND command;
    command.record = D_00325608;
    command.pair_amount.pair = *pair;
    func_001FD250(state, &command.record);
}
