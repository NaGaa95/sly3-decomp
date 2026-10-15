#ifndef SLY3_GAIN_CONTROL_API_H
#define SLY3_GAIN_CONTROL_API_H
/* Independent EE pools: A0 receiver; A1 channel and A2 layer for the channel helper; F12 gain. */
void func_00248A10(void *receiver, float gain);
void func_00248A78(void *receiver, int channel, float gain, int layer);
#endif
