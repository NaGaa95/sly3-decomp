// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
unsigned short *func_002718A0(unsigned short *text, int character);
int func_00271700(const unsigned short *text);
int func_00271448(void *buffer, char *format, ...);
int func_002715F8(const char *text);
void func_001D2898(void *destination, const void *source, unsigned int bytes);
extern char D_00329020[];
int func_002710E8(unsigned short *output, int capacity, const unsigned short *format, const void *arguments)
{
    unsigned short *out = output;
    const char *args = (const char *)arguments;
    char buffer[32];
    int length;
    while (*format) {
        unsigned short *percent = func_002718A0((unsigned short *)format, '%');
        if (percent)
            length = percent - format;
        else {
            length = func_00271700(format);
            percent = (unsigned short *)format + length;
        }
        if (length) {
            if (capacity > 0)
                length = length < capacity ? length : capacity;
            func_001D2898(out, format, length * 2);
            out += length;
            capacity -= length;
            if (capacity == 0)
                break;
            format = percent;
        }
        if (*format == '%') {
            switch (format[1]) {
            case 'd': {
                char *text;
                args += 8;
                func_00271448(buffer, D_00329020, *(int *)(args - 8));
                length = func_002715F8(buffer);
                if (capacity > 0)
                    length = length < capacity ? length : capacity;
                text = buffer;
                while (length-- > 0) {
                    *out++ = *(unsigned char *)text++;
                    capacity--;
                }
                break;
            }
            case 's': {
                const char *text;
                args += 8;
                text = *(const char **)(args - 8);
                length = func_002715F8(text);
                if (capacity > 0)
                    length = length < capacity ? length : capacity;
                while (length-- > 0) {
                    *out++ = *(const unsigned char *)text++;
                    capacity--;
                }
                break;
            }
            case 'S': {
                unsigned short *text;
                args += 8;
                text = *(unsigned short **)(args - 8);
                length = func_00271700(text);
                if (capacity > 0)
                    length = length < capacity ? length : capacity;
                func_001D2898(out, text, length * 2);
                out += length;
                capacity -= length;
                break;
            }
            default:
                *out++ = format[1];
                capacity--;
                break;
            }
            if (capacity == 0)
                break;
            format += 2;
        }
    }
    return out - output;
}
