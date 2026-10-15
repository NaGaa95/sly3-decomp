/* Original module02 device records start at0x26280 and have388-byte stride.
 * Two ports with four slots occupy3104 bytes before the adjacent buffer.
 * Only the reviewed fields are named; the larger original tail stays opaque.
 */
struct McDeviceView {
    unsigned char superblockPrefix[336];
    unsigned char cardType;
    unsigned char unknown151[15];
    int cardFormat;
    unsigned char unknown164[32];
};
typedef char assert_mc_device_stride[(sizeof(struct McDeviceView) == 388) ? 1 : -1];
typedef char assert_mc_type_offset[((unsigned int)&((struct McDeviceView *)0)->cardType == 336) ? 1 : -1];
typedef char assert_mc_format_offset[((unsigned int)&((struct McDeviceView *)0)->cardFormat == 352) ? 1 : -1];
extern struct McDeviceView mcman_device_infos[2][4];
typedef char assert_mc_array_bytes[(sizeof(mcman_device_infos) == 3104) ? 1 : -1];
