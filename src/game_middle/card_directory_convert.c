// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "card_directory_records.h"
void *func_00292034(void *destination, int value, unsigned int bytes);
/* Current recovered string wrapper carries its two actual pointer addresses
 * in integer words and returns the destination address; this caller ignores it. */
int func_00271628(int destination_address, int source_address);

void func_001CE8F0(const struct CardDirectoryRecord *input,
                  struct CardConvertedRecord *output)
{
    func_00292034(output, 0, 0x5C);
    func_00271628((int)output, (int)input->name);
    output->file_bytes = input->file_bytes;
    if (input->attributes & 1) output->flags_and_date.flags_word |= 1;
    if (input->attributes & 2) output->flags_and_date.flags_word |= 2;
    if (input->attributes & 4) output->flags_and_date.flags_word |= 4;
    if (input->attributes & 8) output->flags_and_date.flags_word |= 8;
    if (input->attributes & 0x20) output->flags_and_date.flags_word |= 0x10;
    if (input->attributes & 0x80) output->flags_and_date.flags_word |= 0x20;
    if (input->attributes & 0x800) output->flags_and_date.flags_word |= 0x40;
    if (input->attributes & 0x1000) output->flags_and_date.flags_word |= 0x80;

    output->flags_and_date.parts.month = input->created.month;
    output->flags_and_date.parts.day = input->created.day;
    output->created_year = input->created.year;
    output->created_hour = input->created.hour;
    output->created_minute = input->created.minute;
    output->created_second = input->created.second;
    output->modified_month = input->modified.month;
    output->modified_day = input->modified.day;
    output->modified_year = input->modified.year;
    output->modified_hour = input->modified.hour;
    output->modified_minute = input->modified.minute;
    output->modified_second = input->modified.second;
}
