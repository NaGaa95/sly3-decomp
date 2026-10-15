// Recovered screen conversion fields; names remain provisional.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct COORDINATE_CONVERSION_FIELDS {
    void *vtable;
    int widthSelector;
    int heightSelector;
    int unknownC;
    int divisor;
};
extern "C" int func_002BC640(COORDINATE_CONVERSION_FIELDS *,int value) {
    return value;
}
extern "C" int func_002BC648(COORDINATE_CONVERSION_FIELDS *conversion,int value) {
    return value/conversion->divisor;
}
extern "C" int func_002BC668(COORDINATE_CONVERSION_FIELDS *,int value) {
    return value*16;
}
extern "C" int func_002BC670(COORDINATE_CONVERSION_FIELDS *,int value) {
    return value*16;
}
extern "C" float func_002BE228(COORDINATE_CONVERSION_FIELDS *,float value) {
    return value;
}

extern "C" float func_002BE230(COORDINATE_CONVERSION_FIELDS *conversion,float value) {
    return value/(float)conversion->divisor;
}
extern "C" float func_002BE248(COORDINATE_CONVERSION_FIELDS *conversion,float value) {
    return value+(float)(2048-func_002BC640(conversion,conversion->widthSelector)/2);
}
extern "C" float func_002BE298(COORDINATE_CONVERSION_FIELDS *conversion,float value) {
    return value+(float)(2048-func_002BC648(conversion,conversion->heightSelector)/2);
}
extern "C" int func_002BE320(COORDINATE_CONVERSION_FIELDS *conversion,int value) {
    int offset=2048-func_002BC640(conversion,conversion->widthSelector)/2;return value+offset;
}
extern "C" int func_002BE360(COORDINATE_CONVERSION_FIELDS *conversion,int value) {
    int offset=2048-func_002BC648(conversion,conversion->heightSelector)/2;return value+offset;
}
extern "C" float func_002BE2E8(COORDINATE_CONVERSION_FIELDS *,float value) {
    return value*16.0f;
}
extern "C" float func_002BE2F8(COORDINATE_CONVERSION_FIELDS *,float value) {
    return value*16.0f;
}
