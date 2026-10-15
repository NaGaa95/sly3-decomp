// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct RUMBLE;
struct RUMPAT { char ab[0x104]; };
enum RUMK { RUMK_Nil = -1 };
extern RUMPAT D_00348068[];
void TriggerRumbleRumpat(RUMBLE *prumble, RUMPAT *prumpat, float dt);
extern "C" void func_00210BD8(RUMBLE *prumble, RUMK rumk, float dt)
{
    TriggerRumbleRumpat(prumble, &D_00348068[rumk], dt);
}
