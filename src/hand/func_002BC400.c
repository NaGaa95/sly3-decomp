// Copy all three float coordinates from the explicit source and return the destination.
// Reference algorithm: src/hand/func_0014FCC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { float x, y, z; };
struct V *func_002BC400(struct V *destination, const struct V *source)
{
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
    return destination;
}
