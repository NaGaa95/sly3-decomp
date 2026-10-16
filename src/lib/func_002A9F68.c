// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0

typedef struct RuntimeMpegPictureStateView {
    unsigned char opaque00[0xC4];
    int request_c4;
    unsigned char opaqueC8[0xEC - 0xC8];
    unsigned int output_address;
    int state_f0;
    int state_f4;
    int output_size;
} RuntimeMpegPictureStateView;

typedef struct RuntimeMpegPictureOwnerView {
    unsigned char opaque00[0x40];
    RuntimeMpegPictureStateView *state;
} RuntimeMpegPictureOwnerView;

int func_002A9700(void *decoder);

int func_002A9F68(void *decoder, void *picture, int size)
{
    RuntimeMpegPictureStateView *state =
        ((RuntimeMpegPictureOwnerView *)decoder)->state;
    state->request_c4 = 1;
    state->output_address = ((unsigned int)picture & 0x0FFFFFFF) | 0x20000000;
    state->output_size = size;
    state->state_f4 = 0;
    state->state_f0 = 0;
    return func_002A9700(decoder);
}

#define MPEG_PICTURE_OFFSET(type, field) ((unsigned int)&((type *)0)->field)
typedef char RuntimeMpegPictureLayoutCheck[
    (sizeof(void *) == 4 && sizeof(int) == 4 &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureOwnerView, state) == 0x40 &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureStateView, request_c4) == 0xC4 &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureStateView, output_address) == 0xEC &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureStateView, state_f0) == 0xF0 &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureStateView, state_f4) == 0xF4 &&
     MPEG_PICTURE_OFFSET(RuntimeMpegPictureStateView, output_size) == 0xF8) ? 1 : -1];
#undef MPEG_PICTURE_OFFSET
