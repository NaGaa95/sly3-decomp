/* The original factory returns its constructed sound receiver. */
void *func_00245A30(void *receiver, int identifier);
void *func_00245FA0(unsigned int requested_bytes);

void *func_002459F8(int identifier)
{
    return func_00245A30(func_00245FA0(0x70), identifier);
}
