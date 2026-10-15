// SLY3_CFLAGS: -O2 -G0
// The ninth stack argument is loaded as a 64-bit EE value.
// mode(DI) names that width explicitly; EE long long is 128-bit.
typedef int CallbackArgument __attribute__((mode(DI)));
extern int func_00291290(int command, int payload_size, const void *payload);
extern int func_002914C0(int command, int payload_size, const void *payload,
                       int callback, CallbackArgument callback_argument);

int func_00290ED0(int arg)
{
    int payload[1];
    payload[0] = arg;
    return func_00291290(10, 4, payload);
}

int func_00290F00(int arg)
{
    int payload[1];
    payload[0] = arg;
    return func_002914C0(11, 4, payload, 0, 0);
}

int func_00290F50(int arg0, int arg1)
{
    int payload[2];
    payload[0] = arg0;
    payload[1] = arg1;
    return func_00291290(26, 8, payload);
}

int func_00291000(int arg)
{
    int payload[1];
    payload[0] = arg;
    return func_002914C0(21, 4, payload, 0, 0);
}

int func_00291148(int arg, int callback, CallbackArgument callback_argument)
{
    int payload[1];
    payload[0] = arg;
    return func_002914C0(25, 4, payload, callback, callback_argument);
}

int func_00291218(int arg0, int arg1, int arg2, int arg3)
{
    int payload[4];
    payload[0] = arg0;
    payload[1] = arg1;
    payload[2] = arg2;
    payload[3] = arg3;
    return func_002914C0(34, 16, payload, 0, 0);
}

int func_00291B88(void)
{
    return func_00291290(61, 0, 0);
}

int func_00291C78(void)
{
    return func_00291290(91, 0, 0);
}

int func_00291D30(int arg0, int arg1, int arg2, int arg3,
                  int arg4, int arg5, int arg6, int callback,
                  CallbackArgument callback_argument)
{
    int payload[7];
    payload[0] = arg0;
    payload[1] = arg1;
    payload[2] = arg2;
    payload[3] = arg3;
    payload[4] = arg4;
    payload[5] = arg5;
    payload[6] = arg6;
    return func_002914C0(76, 28, payload, callback, callback_argument);
}
