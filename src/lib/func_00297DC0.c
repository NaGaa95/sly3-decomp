// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0

int func_00297BB8(void *iop_buffer, int argument_bytes,
                  const char *arguments, int *module_result);

int func_00297DC0(void *iop_buffer, int argument_bytes, const char *arguments)
{
    int module_result;
    return func_00297BB8(iop_buffer, argument_bytes, arguments, &module_result);
}

typedef char RuntimeModuleResultWidth4[(sizeof(int) == 4) ? 1 : -1];
