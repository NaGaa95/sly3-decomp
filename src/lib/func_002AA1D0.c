// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct RuntimeMpegReferenceImageView {
    char opaque00[0x28];
    int status;
} RuntimeMpegReferenceImageView;

typedef struct RuntimeMpegReferenceStateView {
    char opaque00[0x1C8];
    RuntimeMpegReferenceImageView *first0;
    RuntimeMpegReferenceImageView *second0;
    int opaque1D0[2];
    RuntimeMpegReferenceImageView *first1;
    RuntimeMpegReferenceImageView *second1;
    int opaque1E0[2];
    RuntimeMpegReferenceImageView *first2;
    RuntimeMpegReferenceImageView *second2;
} RuntimeMpegReferenceStateView;

typedef struct RuntimeMpegReferenceOwnerView {
    char opaque00[0x40];
    RuntimeMpegReferenceStateView *state;
} RuntimeMpegReferenceOwnerView;

int func_002AA1D0(RuntimeMpegReferenceOwnerView *owner)
{
    RuntimeMpegReferenceStateView *state = owner->state;
    if (state->first0) state->first0->status = 0;
    if (state->first1) state->first1->status = 0;
    if (state->first2) state->first2->status = 0;
    if (state->second0) state->second0->status = 0;
    if (state->second1) state->second1->status = 0;
    if (state->second2) state->second2->status = 0;
    return 1;
}
