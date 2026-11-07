// Sly 2 counterpart: _motionVectors (decomp src/lib/_motionVectors.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
int func_002B0B78(void *ctx, int n);
void func_002AFBF8(void *ctx, int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale, int full_pel_vector);
void func_002B0020(void *ctx, int PMV[2][2][2], int *dmvector, int motion_vertical_field_select[2][2], int s,
                    int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale)
{
    if (motion_vector_count == 1) {
        if (mv_format == 0 && !dmv) {
            motion_vertical_field_select[1][s] = motion_vertical_field_select[0][s] = func_002B0B78(ctx, 1);
        }
        func_002AFBF8(ctx, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        motion_vertical_field_select[0][s] = func_002B0B78(ctx, 1);
        func_002AFBF8(ctx, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        motion_vertical_field_select[1][s] = func_002B0B78(ctx, 1);
        func_002AFBF8(ctx, PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}
