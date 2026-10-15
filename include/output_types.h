#ifndef PRIVATE_TEXT_OUTPUT_TYPES_H
#define PRIVATE_TEXT_OUTPUT_TYPES_H

/* This is the same original 0x420-byte view used by admitted func_00271328. */
struct Output {
    void *memory;
    int capacity;
    int position;
    int handle;
    int total;
    int buffer_capacity;
    int buffer_count;
    char *buffer;
    char inline_buffer[0x400];
};

struct Output *func_0025A210(struct Output *, void *memory, int capacity, int buffer_capacity);
int func_00271008(struct Output *, const char *format, void *arguments);
void func_0025A288(struct Output *, int flags);

typedef char OutputSize[(sizeof(struct Output) == 0x420) ? 1 : -1];

#endif
