// Complete original semaphore-request wrapper; remaining request words stay zero.
// SLY3_CFLAGS: -Os -G0
struct EE_SEMA {
    int reserved0;
    int maximum_count;
    int initial_count;
    int reservedC[3];
};
typedef char SemaphoreRequestWidth[(sizeof(struct EE_SEMA) == 24) ? 1 : -1];
void *func_00292034(void *, int, unsigned int);
int func_002936A0(struct EE_SEMA *);

int func_00271B20(int initial_count, int maximum_count)
{
    struct EE_SEMA request;
    func_00292034(&request, 0, sizeof(request));
    request.initial_count = initial_count;
    request.maximum_count = maximum_count;
    return func_002936A0(&request);
}
