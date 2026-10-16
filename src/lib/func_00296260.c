// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

int func_00294198(int microseconds);
int func_00295F08(void *rpc, int command, int mode,
                  void *send, int send_size, void *receive, int receive_size,
                  void *callback, void *callback_argument);

int func_00296260(void *rpc, int command, int mode,
                  void *send, int send_size, void *receive, int receive_size,
                  void *callback, void *callback_argument, int no_retry)
{
    int attempts = 0;
    int backoff = 1;
    int failed;

    do {
        failed = func_00295F08(rpc, command, mode, send, send_size,
                              receive, receive_size, callback,
                              callback_argument) < 0;
        if (!failed || no_retry) {
            break;
        }
        func_00294198(backoff * 1000);
        if (backoff < 127) {
            backoff *= 2;
        }
        ++attempts;
    } while (attempts < 101);

    return failed;
}
