#ifndef SLY3_MASK_FORMATTER_DATA_H
#define SLY3_MASK_FORMATTER_DATA_H
struct MASK_CHARACTER {
    unsigned int mask;
    unsigned char character;
};
struct MASK_CHARACTER_TABLE {
    struct MASK_CHARACTER records[16];
};
extern const struct MASK_CHARACTER_TABLE D_003294A8;
extern const char D_00329528[7];
typedef char mask_character_record_is_8[sizeof(struct MASK_CHARACTER) == 8 ? 1 : -1];
typedef char mask_character_table_is_128[sizeof(struct MASK_CHARACTER_TABLE) == 128 ? 1 : -1];
#endif
