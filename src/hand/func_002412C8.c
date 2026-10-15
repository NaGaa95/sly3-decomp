// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
void func_00241460(void *, float);
void func_002413E0(void *, float);
void func_002412C8(void *p, float f)
{
    if (f <= 0.0f) {
        func_00241460(p, 0.0f);
        func_002413E0(p, 0.0f);
    } else {
        func_00241460(p, -1.0f / f);
    }
}
