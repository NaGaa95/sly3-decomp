/* Original18C3C/68: negative conversion, scale fallthrough, default branch. */
typedef char SndVolumeIntMustBe32Bits[sizeof(int) == 4 ? 1 : -1];
int snd_resolve_volume(int default_volume, int volume)
{
    if (volume < 0)
        volume = (int)(0U - (unsigned int)volume);
    else if (volume != 0x7fffffff)
        volume = (int)((unsigned int)volume * 127U) >> 10;
    else
        volume = default_volume;
    if (volume > 127)
        volume = 127;
    return volume;
}
