// SLY3_CFLAGS: -Os -G0
// Original scalar mask-to-index mapper; names beyond its measured inputs are provisional.
int func_001A9E90(int mask) {
    int index=-1;
    switch(mask) {
        case 64:index=3;
        break;
        case 32:index=4;
        break;
        case 16:index=5;
        break;
        case 128:index=6;
        break;
        case 4:index=9;
        break;
        case 1:index=10;
        break;
        case 512:index=12;
        break;
        case 8:index=7;
        break;
        case 2:index=8;
        break;
        case 1024:index=11;
        break;
    }
    return index;
}
