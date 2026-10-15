#ifndef SLY3_CARD_DIRECTORY_RECORDS_H
#define SLY3_CARD_DIRECTORY_RECORDS_H
struct CardRawTime {
    unsigned char unused0, second, minute, hour, day, month;
    unsigned short year;
};
struct CardDirectoryRecord {
    struct CardRawTime created, modified;
    unsigned int file_bytes;
    unsigned short attributes;
    unsigned char unused16[0x20 - 0x16];
    char name[0x20];
};
union CardFlagsAndDatePrefix {
    unsigned int flags_word;
    struct {
        unsigned short attributes;
        unsigned char month, day;
    } parts;
};
struct CardConvertedRecord {
    unsigned char name_prefix[0x44];
    unsigned int file_bytes;
    union CardFlagsAndDatePrefix flags_and_date;
    unsigned short created_year;
    unsigned char created_hour, created_minute, created_second, unused51;
    unsigned char modified_month, modified_day;
    unsigned short modified_year;
    unsigned char modified_hour, modified_minute, modified_second;
    unsigned char unused59[3];
};
typedef char directory_stride64[(sizeof(struct CardDirectoryRecord) == 64) ? 1 : -1];
typedef char converted_stride92[(sizeof(struct CardConvertedRecord) == 92) ? 1 : -1];
#endif
