// SLY3_CFLAGS: -Os -G0
struct DigitObject { unsigned char prefix[0x140]; int value; };
struct DigitCounter { unsigned char prefix[0x1A4]; int count; struct DigitObject *digits[6]; int number; };
void func_00171740(struct DigitCounter *counter)
{
    int index=counter->count-1;
    int number;
    for(number=counter->number; number>0; number/=10) {
        int digit=number%10;
        if(index>=0) {
            counter->digits[index]->value=digit;
            index--;
        }
    }
}
