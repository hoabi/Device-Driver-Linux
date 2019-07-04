/*
 * s32g275 pinctrl driver based on imx pinmux and pinconf core
 *
 * Copyright 2015-2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-s32.h"

enum s32_pins {
	S32G275_MSCR_PA_00 =  0,
	S32G275_MSCR_PA_01 =  1,
	S32G275_MSCR_PA_02 =  2,
	S32G275_MSCR_PA_03 =  3,
	S32G275_MSCR_PA_04 =  4,
	S32G275_MSCR_PA_05 =  5,
	S32G275_MSCR_PA_06 =  6,
	S32G275_MSCR_PA_07 =  7,
	S32G275_MSCR_PA_08 =  8,
	S32G275_MSCR_PA_09 =  9,
	S32G275_MSCR_PA_10 =  10,
	S32G275_MSCR_PA_11 =  11,
	S32G275_MSCR_PA_12 =  12,
	S32G275_MSCR_PA_13 =  13,
	S32G275_MSCR_PA_14 =  14,
	S32G275_MSCR_PA_15 =  15,
	S32G275_MSCR_PB_00 =  16,
	S32G275_MSCR_PB_01 =  17,
	S32G275_MSCR_PB_02 =  18,
	S32G275_MSCR_PB_03 =  19,
	S32G275_MSCR_PB_04 =  20,
	S32G275_MSCR_PB_05 =  21,
	S32G275_MSCR_PB_06 =  22,
	S32G275_MSCR_PB_07 =  23,
	S32G275_MSCR_PB_08 =  24,
	S32G275_MSCR_PB_09 =  25,
	S32G275_MSCR_PB_10 =  26,
	S32G275_MSCR_PB_11 =  27,
	S32G275_MSCR_PB_12 =  28,
	S32G275_MSCR_PB_13 =  29,
	S32G275_MSCR_PB_14 =  30,
	S32G275_MSCR_PB_15 =  31,
	S32G275_MSCR_PC_00 =  32,
	S32G275_MSCR_PC_01 =  33,
	S32G275_MSCR_PC_02 =  34,
	S32G275_MSCR_PC_03 =  35,
	S32G275_MSCR_PC_04 =  36,
	S32G275_MSCR_PC_05 =  37,
	S32G275_MSCR_PC_06 =  38,
	S32G275_MSCR_PC_07 =  39,
	S32G275_MSCR_PC_08 =  40,
	S32G275_MSCR_PC_09 =  41,
	S32G275_MSCR_PC_10 =  42,
	S32G275_MSCR_PC_11 =  43,
	S32G275_MSCR_PC_12 =  44,
	S32G275_MSCR_PC_13 =  45,
	S32G275_MSCR_PC_14 =  46,
	S32G275_MSCR_PC_15 =  47,
	S32G275_MSCR_PD_00 =  48,
	S32G275_MSCR_PD_01 =  49,
	S32G275_MSCR_PD_02 =  50,
	S32G275_MSCR_PD_03 =  51,
	S32G275_MSCR_PD_04 =  52,
	S32G275_MSCR_PD_05 =  53,
	S32G275_MSCR_PD_06 =  54,
	S32G275_MSCR_PD_07 =  55,
	S32G275_MSCR_PD_08 =  56,
	S32G275_MSCR_PD_09 =  57,
	S32G275_MSCR_PD_10 =  58,
	S32G275_MSCR_PD_11 =  59,
	S32G275_MSCR_PD_12 =  60,
	S32G275_MSCR_PD_13 =  61,
	S32G275_MSCR_PD_14 =  62,
	S32G275_MSCR_PD_15 =  63,
	S32G275_MSCR_PE_00 =  64,
	S32G275_MSCR_PE_01 =  65,
	S32G275_MSCR_PE_02 =  66,
	S32G275_MSCR_PE_03 =  67,
	S32G275_MSCR_PE_04 =  68,
	S32G275_MSCR_PE_05 =  69,
	S32G275_MSCR_PE_06 =  70,
	S32G275_MSCR_PE_07 =  71,
	S32G275_MSCR_PE_08 =  72,
	S32G275_MSCR_PE_09 =  73,
	S32G275_MSCR_PE_10 =  74,
	S32G275_MSCR_PE_11 =  75,
	S32G275_MSCR_PE_12 =  76,
	S32G275_MSCR_PE_13 =  77,
	S32G275_MSCR_PE_14 =  78,
	S32G275_MSCR_PE_15 =  79,
	S32G275_MSCR_PF_00 =  80,
	S32G275_MSCR_PF_01 =  81,
	S32G275_MSCR_PF_02 =  82,
	S32G275_MSCR_PF_03 =  83,
	S32G275_MSCR_PF_04 =  84,
	S32G275_MSCR_PF_05 =  85,
	S32G275_MSCR_PF_06 =  86,
	S32G275_MSCR_PF_07 =  87,
	S32G275_MSCR_PF_08 =  88,
	S32G275_MSCR_PF_09 =  89,
	S32G275_MSCR_PF_10 =  90,
	S32G275_MSCR_PF_11 =  91,
	S32G275_MSCR_PF_12 =  92,
	S32G275_MSCR_PF_13 =  93,
	S32G275_MSCR_PF_14 =  94,
	S32G275_MSCR_PF_15 =  95,
	S32G275_MSCR_PG_00 =  96,
	S32G275_MSCR_PG_01 =  97,
	S32G275_MSCR_PG_02 =  98,
	S32G275_MSCR_PG_03 =  99,
	S32G275_MSCR_PG_04 =  100,
	S32G275_MSCR_PG_05 =  101,
	S32G275_MSCR_PH_00 =  112,
	S32G275_MSCR_PH_01 =  113,
	S32G275_MSCR_PH_02 =  114,
	S32G275_MSCR_PH_03 =  115,
	S32G275_MSCR_PH_04 =  116,
	S32G275_MSCR_PH_05 =  117,
	S32G275_MSCR_PH_06 =  118,
	S32G275_MSCR_PH_07 =  119,
	S32G275_MSCR_PH_08 =  120,
	S32G275_MSCR_PH_09 =  121,
	S32G275_MSCR_PH_10 =  122,
	S32G275_MSCR_PJ_00 =  144,
	S32G275_MSCR_PJ_01 =  145,
	S32G275_MSCR_PJ_02 =  146,
	S32G275_MSCR_PJ_03 =  147,
	S32G275_MSCR_PJ_04 =  148,
	S32G275_MSCR_PJ_05 =  149,
	S32G275_MSCR_PJ_06 =  150,
	S32G275_MSCR_PJ_07 =  151,
	S32G275_MSCR_PJ_08 =  152,
	S32G275_MSCR_PJ_09 =  153,
	S32G275_MSCR_PJ_10 =  154,
	S32G275_MSCR_PJ_11 =  155,
	S32G275_MSCR_PJ_12 =  156,
	S32G275_MSCR_PJ_13 =  157,
	S32G275_MSCR_PJ_14 =  158,
	S32G275_MSCR_PJ_15 =  159,
	S32G275_MSCR_PK_00 =  160,
	S32G275_MSCR_PK_01 =  161,
	S32G275_MSCR_PK_02 =  162,
	S32G275_MSCR_PK_03 =  163,
	S32G275_MSCR_PK_04 =  164,
	S32G275_MSCR_PK_05 =  165,
	S32G275_MSCR_PK_06 =  166,
	S32G275_MSCR_PK_07 =  167,
	S32G275_MSCR_PK_08 =  168,
	S32G275_MSCR_PK_09 =  169,
	S32G275_MSCR_PK_10 =  170,
	S32G275_MSCR_PK_11 =  171,
	S32G275_MSCR_PK_12 =  172,
	S32G275_MSCR_PK_13 =  173,
	S32G275_MSCR_PK_14 =  174,
	S32G275_MSCR_PK_15 =  175,
	S32G275_MSCR_PL_00 =  176,
	S32G275_MSCR_PL_01 =  177,
	S32G275_MSCR_PL_02 =  178,
	S32G275_MSCR_PL_03 =  179,
	S32G275_MSCR_PL_04 =  180,
	S32G275_MSCR_PL_05 =  181,
	S32G275_MSCR_PL_06 =  182,
	S32G275_MSCR_PL_07 =  183,
	S32G275_MSCR_PL_08 =  184,
	S32G275_MSCR_PL_09 =  185,
	S32G275_MSCR_PL_10 =  186,
	S32G275_MSCR_PL_11 =  187,
	S32G275_MSCR_PL_12 =  188,
	S32G275_MSCR_PL_13 =  189,
	S32G275_MSCR_PL_14 =  190,

	S32G275_IMCR_QSPI_A_DATA0 = 540,
	S32G275_IMCR_QSPI_A_DATA1 = 541,
	S32G275_IMCR_QSPI_A_DATA2 = 542,
	S32G275_IMCR_QSPI_A_DATA3 = 543,
	S32G275_IMCR_QSPI_A_DATA4 = 544,
	S32G275_IMCR_QSPI_A_DATA5 = 545,
	S32G275_IMCR_QSPI_A_DATA6 = 546,
	S32G275_IMCR_QSPI_A_DATA7 = 547,
	S32G275_IMCR_QSPI_DQS_A = 548,
	S32G275_IMCR_QSPI_B_DATA0 = 552,
	S32G275_IMCR_QSPI_B_DATA1 = 554,
	S32G275_IMCR_QSPI_B_DATA2 = 551,
	S32G275_IMCR_QSPI_B_DATA3 = 553,
	S32G275_IMCR_QSPI_B_DATA4 = 557,
	S32G275_IMCR_QSPI_B_DATA5 = 550,
	S32G275_IMCR_QSPI_B_DATA6 = 556,
	S32G275_IMCR_QSPI_B_DATA7 = 555,
	S32G275_IMCR_QSPI_DQS_B = 558,
	S32G275_IMCR_BOOT_BOOTMOD0 = 560,
	S32G275_IMCR_BOOT_BOOTMOD1 = 561,
	S32G275_IMCR_I2C0_SCL = 566,
	S32G275_IMCR_I2C0_SDA = 565,
	S32G275_IMCR_LIN0_RX = 512,
	S32G275_IMCR_USDHC_CMD = 515,
	S32G275_IMCR_USDHC_DAT0 = 516,
	S32G275_IMCR_USDHC_DAT1 = 517,
	S32G275_IMCR_USDHC_DAT2 = 520,
	S32G275_IMCR_USDHC_DAT3 = 521,
	S32G275_IMCR_USDHC_DAT4 = 522,
	S32G275_IMCR_USDHC_DAT5 = 523,
	S32G275_IMCR_USDHC_DAT6 = 519,
	S32G275_IMCR_USDHC_DAT7 = 518,
	S32G275_IMCR_USDHC_DQS = 524,
	S32G275_IMCR_CAN0_RXD = 513,
	/* GMAC0 */
	S32G275_IMCR_Ethernet_MDIO = 527,
	S32G275_IMCR_Ethernet_CRS = 526,
	S32G275_IMCR_Ethernet_COL = 525,
	S32G275_IMCR_Ethernet_RX_D0 = 531,
	S32G275_IMCR_Ethernet_RX_D1 = 532,
	S32G275_IMCR_Ethernet_RX_D2 = 533,
	S32G275_IMCR_Ethernet_RX_D3 = 534,
	S32G275_IMCR_Ethernet_RX_ER = 528,
	S32G275_IMCR_Ethernet_RX_CLK = 529,
	S32G275_IMCR_Ethernet_RX_DV = 530,
	S32G275_IMCR_Ethernet_TX_CLK = 538,
	S32G275_IMCR_Ethernet_REF_CLK = 535,

	S32G275_IMCR_FlexRay0_A_RX = 785,
	S32G275_IMCR_FlexRay0_B_RX = 786,
	S32G275_IMCR_FlexTimer0_CH0 = 655,
	S32G275_IMCR_FlexTimer1_CH0 = 665,
	S32G275_IMCR_FlexTimer0_CH1 = 656,
	S32G275_IMCR_FlexTimer1_CH1 = 666,
	S32G275_IMCR_FlexTimer0_CH2 = 657,
	S32G275_IMCR_FlexTimer1_CH2 = 667,
	S32G275_IMCR_FlexTimer0_CH3 = 658,
	S32G275_IMCR_FlexTimer1_CH3 = 668,
	S32G275_IMCR_FlexTimer0_CH4 = 659,
	S32G275_IMCR_FlexTimer1_CH4 = 669,
	S32G275_IMCR_FlexTimer0_CH5 = 660,
	S32G275_IMCR_FlexTimer1_CH5 = 670,
	S32G275_IMCR_FlexTimer0_EXTCLK = 661,
	S32G275_IMCR_FlexTimer1_EXTCLK = 671,
	S32G275_IMCR_I2C1_SCL = 717,
	S32G275_IMCR_I2C1_SDA = 718,
	S32G275_IMCR_I2C2_SCL = 719,
	S32G275_IMCR_I2C2_SDA = 720,
	S32G275_IMCR_I2C3_SCL = 721,
	S32G275_IMCR_I2C3_SDA = 722,
	S32G275_IMCR_I2C4_SCL = 723,
	S32G275_IMCR_I2C4_SDA = 724,
	S32G275_IMCR_LIN1_RX = 736,
	S32G275_IMCR_LIN2_RX = 737,
	S32G275_IMCR_DSPI0_PCS0 = 980,
	S32G275_IMCR_DSPI0_SCK = 981,
	S32G275_IMCR_DSPI0_SIN = 982,
	S32G275_IMCR_DSPI1_PCS0 = 985,
	S32G275_IMCR_DSPI1_SCK = 986,
	S32G275_IMCR_DSPI1_SIN = 987,
	S32G275_IMCR_DSPI2_PCS0 = 990,
	S32G275_IMCR_DSPI2_SCK = 991,
	S32G275_IMCR_DSPI2_SIN = 992,
	S32G275_IMCR_DSPI3_PCS0 = 995,
	S32G275_IMCR_DSPI3_SCK = 996,
	S32G275_IMCR_DSPI3_SIN = 997,
	S32G275_IMCR_DSPI4_PCS0 = 1000,
	S32G275_IMCR_DSPI4_SCK = 1001,
	S32G275_IMCR_DSPI4_SIN = 1002,
	S32G275_IMCR_DSPI5_PCS0 = 1005,
	S32G275_IMCR_DSPI5_SCK = 1006,
	S32G275_IMCR_DSPI5_SIN = 1007,
	S32G275_IMCR_LLCE_CAN0_RXD = 745,
	S32G275_IMCR_LLCE_CAN1_RXD = 746,
	S32G275_IMCR_LLCE_CAN2_RXD = 747,
	S32G275_IMCR_LLCE_CAN3_RXD = 748,
	S32G275_IMCR_LLCE_CAN4_RXD = 749,
	S32G275_IMCR_LLCE_CAN5_RXD = 750,
	S32G275_IMCR_LLCE_CAN6_RXD = 751,
	S32G275_IMCR_LLCE_CAN7_RXD = 752,
	S32G275_IMCR_LLCE_CAN8_RXD = 753,
	S32G275_IMCR_LLCE_CAN9_RXD = 754,
	S32G275_IMCR_LLCE_CAN10_RXD = 755,
	S32G275_IMCR_LLCE_CAN11_RXD = 756,
	S32G275_IMCR_LLCE_CAN12_RXD = 757,
	S32G275_IMCR_LLCE_CAN13_RXD = 758,
	S32G275_IMCR_LLCE_CAN14_RXD = 759,
	S32G275_IMCR_LLCE_CAN15_RXD = 760,

	S32G275_IMCR_SIUL_EIRQ0 =  910,
	S32G275_IMCR_SIUL_EIRQ1 =  911,
	S32G275_IMCR_SIUL_EIRQ2 =  912,
	S32G275_IMCR_SIUL_EIRQ3 =  913,
	S32G275_IMCR_SIUL_EIRQ4 =  914,
	S32G275_IMCR_SIUL_EIRQ5 =  915,
	S32G275_IMCR_SIUL_EIRQ6 =  916,
	S32G275_IMCR_SIUL_EIRQ7 =  917,
	S32G275_IMCR_SIUL_EIRQ8 =  918,
	S32G275_IMCR_SIUL_EIRQ9 =  919,
	S32G275_IMCR_SIUL_EIRQ10 =  920,
	S32G275_IMCR_SIUL_EIRQ11 =  921,
	S32G275_IMCR_SIUL_EIRQ12 =  922,
	S32G275_IMCR_SIUL_EIRQ13 =  923,
	S32G275_IMCR_SIUL_EIRQ14 =  924,
	S32G275_IMCR_SIUL_EIRQ15 =  925,
	S32G275_IMCR_SIUL_EIRQ16 =  926,
	S32G275_IMCR_SIUL_EIRQ17 =  927,
	S32G275_IMCR_SIUL_EIRQ18 =  928,
	S32G275_IMCR_SIUL_EIRQ19 =  929,
	S32G275_IMCR_SIUL_EIRQ20 =  930,
	S32G275_IMCR_SIUL_EIRQ21 =  931,
	S32G275_IMCR_SIUL_EIRQ22 =  932,
	S32G275_IMCR_SIUL_EIRQ23 =  933,
	S32G275_IMCR_SIUL_EIRQ24 =  934,
	S32G275_IMCR_SIUL_EIRQ25 =  935,
	S32G275_IMCR_SIUL_EIRQ26 =  936,
	S32G275_IMCR_SIUL_EIRQ27 =  937,
	S32G275_IMCR_SIUL_EIRQ28 =  938,
	S32G275_IMCR_SIUL_EIRQ29 =  939,
	S32G275_IMCR_SIUL_EIRQ30 =  940,
	S32G275_IMCR_SIUL_EIRQ31 =  941,
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc s32_pinctrl_pads_siul2_0[] = {
	S32_PINCTRL_PIN(S32G275_MSCR_PA_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PA_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PB_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PC_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PD_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PE_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PF_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PG_05),

	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA0),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA1),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA2),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA3),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA4),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA5),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA6),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_A_DATA7),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_DQS_A),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA0),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA1),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA2),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA3),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA4),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA5),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA6),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_B_DATA7),
	S32_PINCTRL_PIN(S32G275_IMCR_QSPI_DQS_B),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C0_SCL),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C0_SDA),
	S32_PINCTRL_PIN(S32G275_IMCR_LIN0_RX),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_CMD),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT0),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT1),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT2),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT3),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT4),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT5),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT6),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DAT7),
	S32_PINCTRL_PIN(S32G275_IMCR_USDHC_DQS),
	S32_PINCTRL_PIN(S32G275_IMCR_CAN0_RXD),
	/* GMAC0 */
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_MDIO),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_CRS),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_COL),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_D0),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_D1),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_D2),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_D3),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_ER),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_CLK),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_RX_DV),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_TX_CLK),
	S32_PINCTRL_PIN(S32G275_IMCR_Ethernet_REF_CLK),
};

static const struct pinctrl_pin_desc s32_pinctrl_pads_siul2_1[] = {
	S32_PINCTRL_PIN(S32G275_MSCR_PH_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PH_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PJ_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_14),
	S32_PINCTRL_PIN(S32G275_MSCR_PK_15),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_00),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_01),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_02),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_03),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_04),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_05),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_06),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_07),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_08),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_09),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_10),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_11),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_12),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_13),
	S32_PINCTRL_PIN(S32G275_MSCR_PL_14),

	S32_PINCTRL_PIN(S32G275_IMCR_FlexRay0_A_RX),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexRay0_B_RX),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH0),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH0),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH1),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH1),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH2),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH2),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH3),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH3),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH4),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH4),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_CH5),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_CH5),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer0_EXTCLK),
	S32_PINCTRL_PIN(S32G275_IMCR_FlexTimer1_EXTCLK),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C1_SCL),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C1_SDA),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C2_SCL),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C2_SDA),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C3_SCL),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C3_SDA),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C4_SCL),
	S32_PINCTRL_PIN(S32G275_IMCR_I2C4_SDA),
	S32_PINCTRL_PIN(S32G275_IMCR_LIN1_RX),
	S32_PINCTRL_PIN(S32G275_IMCR_LIN2_RX),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI0_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI0_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI0_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI1_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI1_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI1_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI2_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI2_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI2_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI3_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI3_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI3_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI4_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI4_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI4_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI5_PCS0),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI5_SCK),
	S32_PINCTRL_PIN(S32G275_IMCR_DSPI5_SIN),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN0_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN1_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN2_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN3_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN4_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN5_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN6_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN7_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN8_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN9_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN10_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN11_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN12_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN13_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN14_RXD),
	S32_PINCTRL_PIN(S32G275_IMCR_LLCE_CAN15_RXD),

	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ0),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ1),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ2),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ3),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ4),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ5),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ6),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ7),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ8),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ9),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ10),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ11),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ12),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ13),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ14),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ15),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ16),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ17),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ18),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ19),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ20),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ21),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ22),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ23),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ24),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ25),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ26),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ27),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ28),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ29),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ30),
	S32_PINCTRL_PIN(S32G275_IMCR_SIUL_EIRQ31),
};

static struct s32_pinctrl_soc_info s32_pinctrl_info_0 = {
	.pins = s32_pinctrl_pads_siul2_0,
	.npins = ARRAY_SIZE(s32_pinctrl_pads_siul2_0),
};

static struct s32_pinctrl_soc_info s32_pinctrl_info_1 = {
	.pins = s32_pinctrl_pads_siul2_1,
	.npins = ARRAY_SIZE(s32_pinctrl_pads_siul2_1),
};

static const struct of_device_id s32_pinctrl_of_match[] = {
	{
		.compatible = "fsl,s32g275-siul2_0-pinctrl",
		.data = (void *) &s32_pinctrl_info_0,
	},
	{
		.compatible = "fsl,s32g275-siul2_1-pinctrl",
		.data = (void *) &s32_pinctrl_info_1,
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, s32_pinctrl_of_match);

static int s32g275_pinctrl_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
		of_match_device(s32_pinctrl_of_match, &pdev->dev);

	if (!of_id)
		return -ENODEV;

	return s32_pinctrl_probe
			(pdev, (struct s32_pinctrl_soc_info *) of_id->data);
}

static struct platform_driver s32g275_pinctrl_driver = {
	.driver = {
		.name = "s32g275-siul2-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = s32_pinctrl_of_match,
	},
	.probe = s32g275_pinctrl_probe,
	.remove = s32_pinctrl_remove,
};

module_platform_driver(s32g275_pinctrl_driver);

MODULE_AUTHOR("Matthew Nunez <matthew.nunez@nxp.com>");
MODULE_DESCRIPTION("NXP S32G275 pinctrl driver");
MODULE_LICENSE("GPL v2");
