// SLY3_CFLAGS: -Os -G0
#include "../P2/mat.h"

typedef struct MATRIX4 Matrix;
typedef struct VECTOR Vector;
struct ChannelModeEntry { short delta, pad; void (*apply)(void *, int); };
struct ChannelModeOwner { char prefix[0xC]; struct ChannelModeEntry *table; };
struct ChannelMode {
    char prefix[0x94];
    int kind;
    short mode;
    char gap9A[0xB0 - 0x9A];
    Vector value;
    char gapC0[0xF0 - 0xC0];
    Vector velocity;
};

int func_0028EFD8(int);
int func_0028F010(int);
int func_0028F048(int);
Matrix func_0028B730(struct ChannelMode *);
Matrix func_0011D768(struct ChannelMode *);
Matrix func_0011D558(Matrix *, Matrix *);
void func_0028B188(struct ChannelModeOwner *, struct ChannelMode *);

static inline void SetVector(Vector *value, float x, float y, float z)
{
    value->x = x;
    value->y = y;
    value->z = z;
}

void func_0028F068(struct ChannelModeOwner *owner, struct ChannelMode *channel, int mode)
{
    if (mode == channel->mode)
        return;
    if (func_0028EFD8(mode) && !func_0028EFD8(channel->mode)) {
        Matrix matrix;
        Matrix temporary;
        temporary = func_0028B730(channel);
        matrix = temporary;
        switch (channel->kind) {
        case 1: case 4: case 5: case 9: case 10:
            channel->value = *(Vector *)matrix.mat[3];
            break;
        case 11:
            SetVector(&channel->value, matrix.mat[1][0], matrix.mat[2][0], matrix.mat[2][1]);
            break;
        case 12:
            SetVector(&channel->value, matrix.mat[0][0], matrix.mat[1][1], matrix.mat[2][2]);
            break;
        case 6: case 7: {
            Matrix inverse = func_0011D768(channel);
            temporary = func_0011D558(&matrix, &inverse);
            matrix = temporary;
            SetVector(&channel->value, matrix.mat[1][2], matrix.mat[2][0], matrix.mat[0][1]);
            break;
        }
        }
    }
    switch (mode) {
    case 1: case 2: case 3:
        if (!func_0028F048(channel->mode)) {
            Vector *velocity = &channel->velocity;
            velocity->z = 0;
            velocity->y = 0;
            velocity->x = 0;
        }
        func_0028B188(owner, channel);
        break;
    case 0: case 14: case 15: case 16: case 17: case 18: case 21: case 22:
        func_0028B188(owner, channel);
        break;
    }
    channel->mode = mode;
    if (!func_0028F010(mode))
        owner->table[51].apply((char *)owner + owner->table[51].delta, 4);
}
