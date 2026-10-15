/* Coefficients derived from primary PS2SDK libsd effect.c.
 * Copyright (c) 2004 TyRaNiD <tiraniddo@hotmail.com>
 * Copyright (c) 2004,2007 Lukasz Bruun <mail@lukasz.dk>
 * See LICENSE.PS2SDK for licensing terms.
 *
 * The original libsd stores a selection mask followed by 16 ordered packed
 * SPU2 register pairs. Mask zero selects every effect parameter. The ordinary
 * initialized records below preserve that actual 68-byte scalar layout.
 * Coefficients are primary-source values; masks/layout are independently
 * evidenced by the original 0x13C parameter writer and all five table uses.
 */
#define COEFFICIENT_PAIR(LOW,HIGH) ((unsigned int)(LOW)|((unsigned int)(HIGH)<<16))
typedef struct ReverbPreset {
    unsigned int selection_mask;
    unsigned int feedback_sources_ab; /* low16 FB_SRC_A, high16 FB_SRC_B */
    unsigned int iir_alpha_accumulator_a; /* low16 IIR_ALPHA, high16 ACC_COEF_A */
    unsigned int accumulator_coefficients_bc; /* low16 ACC_COEF_B, high16 ACC_COEF_C */
    unsigned int accumulator_d_iir_coefficient; /* low16 ACC_COEF_D, high16 IIR_COEF */
    unsigned int feedback_alpha_x; /* low16 FB_ALPHA, high16 FB_X */
    unsigned int iir_destinations_a01; /* low16 IIR_DEST_A0, high16 IIR_DEST_A1 */
    unsigned int accumulator_sources_a01; /* low16 ACC_SRC_A0, high16 ACC_SRC_A1 */
    unsigned int accumulator_sources_b01; /* low16 ACC_SRC_B0, high16 ACC_SRC_B1 */
    unsigned int iir_sources_a01; /* low16 IIR_SRC_A0, high16 IIR_SRC_A1 */
    unsigned int iir_destinations_b01; /* low16 IIR_DEST_B0, high16 IIR_DEST_B1 */
    unsigned int accumulator_sources_c01; /* low16 ACC_SRC_C0, high16 ACC_SRC_C1 */
    unsigned int accumulator_sources_d01; /* low16 ACC_SRC_D0, high16 ACC_SRC_D1 */
    unsigned int iir_sources_b10; /* low16 IIR_SRC_B1, high16 IIR_SRC_B0 */
    unsigned int mixer_destinations_a01; /* low16 MIX_DEST_A0, high16 MIX_DEST_A1 */
    unsigned int mixer_destinations_b01; /* low16 MIX_DEST_B0, high16 MIX_DEST_B1 */
    unsigned int input_coefficients_lr; /* low16 IN_COEF_L, high16 IN_COEF_R */
} ReverbPreset;

ReverbPreset libsd_reverb_presets[10] = {
    { /* OFF */
        0,
        COEFFICIENT_PAIR(0x0000,0x0000) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x0001,0x0001) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x0001,0x0001) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* input_coefficients_lr */
    },
    { /* ROOM */
        0,
        COEFFICIENT_PAIR(0x007D,0x005B) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x6D80,0x54B8) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xBED0,0x0000) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0x0000,0xBA80) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x5800,0x5300) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x04D6,0x0333) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x03F0,0x0227) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0374,0x01EF) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x0336,0x01B7) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x0335,0x01B6) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x0334,0x01B5) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x0334,0x01B5) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x0334,0x01B5) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x01B4,0x0136) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x00B8,0x005C) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* STUDIO_1 */
        0,
        COEFFICIENT_PAIR(0x0033,0x0025) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x70F0,0x4FA8) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xBCE0,0x4410) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0xC0F0,0x9C00) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x5280,0x4EC0) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x03E4,0x031B) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x03A4,0x02AF) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0372,0x0266) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x031C,0x025D) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x025C,0x018E) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x022F,0x0135) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x01D2,0x00B7) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x018F,0x00B5) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x00B4,0x0080) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x004C,0x0026) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* STUDIO_2 */
        0,
        COEFFICIENT_PAIR(0x00B1,0x007F) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x70F0,0x4FA8) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xBCE0,0x4510) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0xBEF0,0xB4C0) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x5280,0x4EC0) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x0904,0x076B) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x0824,0x065F) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x07A2,0x0616) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x076C,0x05ED) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x05EC,0x042E) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x050F,0x0305) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x0462,0x02B7) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x042F,0x0265) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x0264,0x01B2) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0100,0x0080) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* STUDIO_3 */
        0,
        COEFFICIENT_PAIR(0x00E3,0x00A9) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x6F60,0x4FA8) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xBCE0,0x4510) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0xBEF0,0xA680) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x5680,0x52C0) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x0DFB,0x0B58) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x0D09,0x0A3C) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0BD9,0x0973) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x0B59,0x08DA) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x08D9,0x05E9) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x07EC,0x04B0) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x06EF,0x03D2) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x05EA,0x031D) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x031C,0x0238) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0154,0x00AA) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* HALL */
        0,
        COEFFICIENT_PAIR(0x01A5,0x0139) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x6000,0x5000) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0x4C00,0xB800) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0xBC00,0xC000) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x6000,0x5C00) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x15BA,0x11BB) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x14C2,0x10BD) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x11BC,0x0DC1) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x11C0,0x0DC3) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x0DC0,0x09C1) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x0BC4,0x07C1) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x0A00,0x06CD) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x09C2,0x05C1) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x05C0,0x041A) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0274,0x013A) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* SPACE */
        0,
        COEFFICIENT_PAIR(0x033D,0x0231) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x7E00,0x5000) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xB400,0xB000) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0x4C00,0xB000) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x6000,0x5400) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x1ED6,0x1A31) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x1D14,0x183B) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x1BC2,0x16B2) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x1A32,0x15EF) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x15EE,0x1055) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x1334,0x0F2D) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x11F6,0x0C5D) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x1056,0x0AE1) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x0AE0,0x07A2) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0464,0x0232) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* ECHO */
        0,
        COEFFICIENT_PAIR(0x0003,0x0003) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x7FFF,0x7FFF) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0x0000,0x8100) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x1FFD,0x0FFD) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x1009,0x0009) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x1009,0x0009) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x1FFF,0x1FFF) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x1008,0x1004) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0008,0x0004) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* DELAY */
        0,
        COEFFICIENT_PAIR(0x0003,0x0003) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x7FFF,0x7FFF) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x1FFD,0x0FFD) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x1009,0x0009) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x0000,0x0000) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x1009,0x0009) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x1FFF,0x1FFF) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x1FFE,0x1FFE) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x1008,0x1004) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0008,0x0004) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    },
    { /* CLEAR */
        0,
        COEFFICIENT_PAIR(0x0017,0x0013) /* feedback_sources_ab */,
        COEFFICIENT_PAIR(0x70F0,0x4FA8) /* iir_alpha_accumulator_a */,
        COEFFICIENT_PAIR(0xBCE0,0x4510) /* accumulator_coefficients_bc */,
        COEFFICIENT_PAIR(0xBEF0,0x8500) /* accumulator_d_iir_coefficient */,
        COEFFICIENT_PAIR(0x5F80,0x54C0) /* feedback_alpha_x */,
        COEFFICIENT_PAIR(0x0371,0x02AF) /* iir_destinations_a01 */,
        COEFFICIENT_PAIR(0x02E5,0x01DF) /* accumulator_sources_a01 */,
        COEFFICIENT_PAIR(0x02B0,0x01D7) /* accumulator_sources_b01 */,
        COEFFICIENT_PAIR(0x0358,0x026A) /* iir_sources_a01 */,
        COEFFICIENT_PAIR(0x01D6,0x011E) /* iir_destinations_b01 */,
        COEFFICIENT_PAIR(0x012D,0x00B1) /* accumulator_sources_c01 */,
        COEFFICIENT_PAIR(0x011F,0x0059) /* accumulator_sources_d01 */,
        COEFFICIENT_PAIR(0x01A0,0x00E3) /* iir_sources_b10 */,
        COEFFICIENT_PAIR(0x0058,0x0040) /* mixer_destinations_a01 */,
        COEFFICIENT_PAIR(0x0028,0x0014) /* mixer_destinations_b01 */,
        COEFFICIENT_PAIR(0x8000,0x8000) /* input_coefficients_lr */
    }
};
