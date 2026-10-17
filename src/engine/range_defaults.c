// SLY3_CFLAGS: -Os -G0
struct RangeDefaults { unsigned char prefix[8]; int id; unsigned char gap0C[0x18-0x0C]; float value18; float value1C; float value20; float value24; };
void func_00162108(struct RangeDefaults *range)
{
    range->id=-1;
    range->value24=1.0f;
    range->value20=0.5f;
    range->value18=3000.0f;
    range->value1C=4000.0f;
}
