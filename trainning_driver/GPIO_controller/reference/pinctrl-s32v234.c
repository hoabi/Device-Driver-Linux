/*
 * s32v234 pinctrl driver based on imx pinmux and pinconf core
 *
 * Copyright 2015-2016 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
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

#include "pinctrl-s32v.h"

enum s32v234_pins {
	S32V234_MSCR_PA0 = 0,
	S32V234_MSCR_PA1 = 1,
	S32V234_MSCR_PA2 = 2,
	S32V234_MSCR_PA3 = 3,
	S32V234_MSCR_PA4 = 4,
	S32V234_MSCR_PA5 = 5,
	S32V234_MSCR_PA6 = 6,
	S32V234_MSCR_PA7 = 7,
	S32V234_MSCR_PA8 = 8,
	S32V234_MSCR_PA9 = 9,
	S32V234_MSCR_PA10 = 10,
	S32V234_MSCR_PA11 = 11,
	S32V234_MSCR_PA12 = 12,
	S32V234_MSCR_PA13 = 13,
	S32V234_MSCR_PA14 = 14,
	S32V234_MSCR_PA15 = 15,
	S32V234_MSCR_PB0 = 16,
	S32V234_MSCR_PB1 = 17,
	S32V234_MSCR_PB2 = 18,
	S32V234_MSCR_PB3 = 19,
	S32V234_MSCR_PB4 = 20,
	S32V234_MSCR_PB5 = 21,
	S32V234_MSCR_PB6 = 22,
	S32V234_MSCR_PB7 = 23,
	S32V234_MSCR_PB8 = 24,
	S32V234_MSCR_PB9 = 25,
	S32V234_MSCR_PB10 = 26,
	S32V234_MSCR_PB11 = 27,
	S32V234_MSCR_PB12 = 28,
	S32V234_MSCR_PB13 = 29,
	S32V234_MSCR_PB14 = 30,
	S32V234_MSCR_PB15 = 31,
	S32V234_MSCR_PC0 = 32,
	S32V234_MSCR_PC1 = 33,
	S32V234_MSCR_PC2 = 34,
	S32V234_MSCR_PC3 = 35,
	S32V234_MSCR_PC4 = 36,
	S32V234_MSCR_PC5 = 37,
	S32V234_MSCR_PC6 = 38,
	S32V234_MSCR_PC7 = 39,
	S32V234_MSCR_PC8 = 40,
	S32V234_MSCR_PC9 = 41,
	S32V234_MSCR_PC10 = 42,
	S32V234_MSCR_PC11 = 43,
	S32V234_MSCR_PC12 = 44,
	S32V234_MSCR_PC13 = 45,
	S32V234_MSCR_PC14 = 46,
	S32V234_MSCR_PC15 = 47,
	S32V234_MSCR_PD0 = 48,
	S32V234_MSCR_PD1 = 49,
	S32V234_MSCR_PD2 = 50,
	S32V234_MSCR_PD3 = 51,
	S32V234_MSCR_PD4 = 52,
	S32V234_MSCR_PD5 = 53,
	S32V234_MSCR_PD6 = 54,
	S32V234_MSCR_PD7 = 55,
	S32V234_MSCR_PD8 = 56,
	S32V234_MSCR_PD9 = 57,
	S32V234_MSCR_PD10 = 58,
	S32V234_MSCR_PD11 = 59,
	S32V234_MSCR_PD12 = 60,
	S32V234_MSCR_PD13 = 61,
	S32V234_MSCR_PD14 = 62,
	S32V234_MSCR_PD15 = 63,
	S32V234_MSCR_PE0 = 64,
	S32V234_MSCR_PE1 = 65,
	S32V234_MSCR_PE2 = 66,
	S32V234_MSCR_PE3 = 67,
	S32V234_MSCR_PE4 = 68,
	S32V234_MSCR_PE5 = 69,
	S32V234_MSCR_PE6 = 70,
	S32V234_MSCR_PE7 = 71,
	S32V234_MSCR_PE8 = 72,
	S32V234_MSCR_PE9 = 73,
	S32V234_MSCR_PE10 = 74,
	S32V234_MSCR_PE11 = 75,
	S32V234_MSCR_PE12 = 76,
	S32V234_MSCR_PE13 = 77,
	S32V234_MSCR_PE14 = 78,
	S32V234_MSCR_PE15 = 79,
	S32V234_MSCR_PF0 = 80,
	S32V234_MSCR_PF1 = 81,
	S32V234_MSCR_PF2 = 82,
	S32V234_MSCR_PF3 = 83,
	S32V234_MSCR_PF4 = 84,
	S32V234_MSCR_PF5 = 85,
	S32V234_MSCR_PF6 = 86,
	S32V234_MSCR_PF7 = 87,
	S32V234_MSCR_PF8 = 88,
	S32V234_MSCR_PF9 = 89,
	S32V234_MSCR_PF10 = 90,
	S32V234_MSCR_PF11 = 91,
	S32V234_MSCR_PF12 = 92,
	S32V234_MSCR_PF13 = 93,
	S32V234_MSCR_PF14 = 94,
	S32V234_MSCR_PF15 = 95,
	S32V234_MSCR_PG0 = 96,
	S32V234_MSCR_PG1 = 97,
	S32V234_MSCR_PG2 = 98,
	S32V234_MSCR_PG3 = 99,
	S32V234_MSCR_PG4 = 100,
	S32V234_MSCR_PG5 = 101,
	S32V234_MSCR_PG6 = 102,
	S32V234_MSCR_PG7 = 103,
	S32V234_MSCR_PG8 = 104,
	S32V234_MSCR_PG9 = 105,
	S32V234_MSCR_PG10 = 106,
	S32V234_MSCR_PG11 = 107,
	S32V234_MSCR_PG12 = 108,
	S32V234_MSCR_PG13 = 109,
	S32V234_MSCR_PG14 = 110,
	S32V234_MSCR_PG15 = 111,
	S32V234_MSCR_PH0 = 112,
	S32V234_MSCR_PH1 = 113,
	S32V234_MSCR_PH2 = 114,
	S32V234_MSCR_PH3 = 115,
	S32V234_MSCR_PH4 = 116,
	S32V234_MSCR_PH5 = 117,
	S32V234_MSCR_PH6 = 118,
	S32V234_MSCR_PH7 = 119,
	S32V234_MSCR_PH8 = 120,
	S32V234_MSCR_PH9 = 121,
	S32V234_MSCR_PH10 = 122,
	S32V234_MSCR_PH11 = 123,
	S32V234_MSCR_PH12 = 124,
	S32V234_MSCR_PH13 = 125,
	S32V234_MSCR_PH14 = 126,
	S32V234_MSCR_PH15 = 127,
	S32V234_MSCR_PJ0 = 128,
	S32V234_MSCR_PJ1 = 129,
	S32V234_MSCR_PJ2 = 130,
	S32V234_MSCR_PJ3 = 131,
	S32V234_MSCR_PJ4 = 132,
	S32V234_MSCR_PJ5 = 133,
	S32V234_MSCR_PJ6 = 134,
	S32V234_MSCR_PJ7 = 135,
	S32V234_MSCR_PJ8 = 136,
	S32V234_MSCR_PJ9 = 137,
	S32V234_MSCR_PJ10 = 138,
	S32V234_MSCR_PJ11 = 139,
	S32V234_MSCR_PJ12 = 140,
	S32V234_MSCR_PJ13 = 141,
	S32V234_MSCR_PJ14 = 142,
	S32V234_MSCR_PJ15 = 143,
	S32V234_MSCR_PK0 = 144,
	S32V234_MSCR_PK1 = 145,
	S32V234_MSCR_PK2 = 146,
	S32V234_MSCR_PK3 = 147,
	S32V234_MSCR_PK4 = 148,
	S32V234_MSCR_PK5 = 149,
	S32V234_MSCR_PK6 = 150,
	S32V234_MSCR_PK7 = 151,
	S32V234_MSCR_PK8 = 152,
	S32V234_MSCR_PK9 = 153,
	S32V234_MSCR_PK10 = 154,
	S32V234_MSCR_PK11 = 155,
	S32V234_MSCR_PK12 = 156,
	S32V234_MSCR_PK13 = 157,
	S32V234_MSCR_PK14 = 158,
	S32V234_MSCR_PK15 = 159,
	S32V234_MSCR_PL0 = 160,
	S32V234_MSCR_PL1 = 161,
	S32V234_MSCR_PL2 = 162,
	S32V234_MSCR_PL3 = 163,
	S32V234_MSCR_PL4 = 164,
	S32V234_MSCR_PL5 = 165,
	S32V234_MSCR_PL8 = 166,

	S32V234_IMCR_QSPI_A_DATA0 = 820,
	S32V234_IMCR_QSPI_A_DATA1 = 821,
	S32V234_IMCR_QSPI_A_DATA2 = 822,
	S32V234_IMCR_QSPI_A_DATA3 = 823,
	S32V234_IMCR_QSPI_A_DATA4 = 824,
	S32V234_IMCR_QSPI_A_DATA5 = 825,
	S32V234_IMCR_QSPI_A_DATA6 = 826,
	S32V234_IMCR_QSPI_A_DATA7 = 827,
	S32V234_IMCR_QSPI_A_DQS = 819,
	S32V234_IMCR_BOOT_BOOTMOD0 = 570,
	S32V234_IMCR_BOOT_BOOTMOD1 = 571,
	S32V234_IMCR_QSPI_B_DATA0 = 829,
	S32V234_IMCR_QSPI_B_DATA1 = 830,
	S32V234_IMCR_QSPI_B_DATA2 = 831,
	S32V234_IMCR_QSPI_B_DATA3 = 832,
	S32V234_IMCR_QSPI_B_DQS = 828,
	S32V234_IMCR_FlexRay_CA_RX = 1012,
	S32V234_IMCR_FlexRay_CB_RX = 1013,
	S32V234_IMCR_FlexTimer0_CH0 = 512,
	S32V234_IMCR_FlexTimer1_CH0 = 521,
	S32V234_IMCR_FlexTimer0_CH1 = 513,
	S32V234_IMCR_FlexTimer1_CH1 = 522,
	S32V234_IMCR_FlexTimer0_CH2 = 514,
	S32V234_IMCR_FlexTimer1_CH2 = 523,
	S32V234_IMCR_FlexTimer0_CH3 = 515,
	S32V234_IMCR_FlexTimer1_CH3 = 524,
	S32V234_IMCR_FlexTimer0_CH4 = 516,
	S32V234_IMCR_FlexTimer1_CH4 = 525,
	S32V234_IMCR_FlexTimer0_CH5 = 517,
	S32V234_IMCR_FlexTimer1_CH5 = 526,
	S32V234_IMCR_IIC0_CLK = 780,
	S32V234_IMCR_IIC1_CLK = 782,
	S32V234_IMCR_IIC2_CLK = 784,
	S32V234_IMCR_USDHC_CLK = 902,
	S32V234_IMCR_USDHC_CMD = 901,
	S32V234_IMCR_Ethernet_COL = 971,
	S32V234_IMCR_Ethernet_CRS = 972,
	S32V234_IMCR_SPI0_CS0 = 802,
	S32V234_IMCR_SPI1_CS0 = 805,
	S32V234_IMCR_SPI2_CS0 = 808,
	S32V234_IMCR_SPI3_CS0 = 811,
	S32V234_IMCR_VIU0_D10 = 635,
	S32V234_IMCR_VIU1_D10 = 670,
	S32V234_IMCR_VIU0_D11 = 636,
	S32V234_IMCR_VIU1_D11 = 671,
	S32V234_IMCR_VIU0_D12 = 637,
	S32V234_IMCR_VIU1_D12 = 672,
	S32V234_IMCR_VIU0_D13 = 638,
	S32V234_IMCR_VIU1_D13 = 673,
	S32V234_IMCR_VIU0_D14 = 639,
	S32V234_IMCR_VIU1_D14 = 674,
	S32V234_IMCR_VIU0_D15 = 640,
	S32V234_IMCR_VIU1_D15 = 675,
	S32V234_IMCR_VIU0_D16 = 641,
	S32V234_IMCR_VIU1_D16 = 676,
	S32V234_IMCR_VIU0_D17 = 642,
	S32V234_IMCR_VIU1_D17 = 677,
	S32V234_IMCR_VIU0_D18 = 643,
	S32V234_IMCR_VIU1_D18 = 678,
	S32V234_IMCR_VIU0_D19 = 644,
	S32V234_IMCR_VIU1_D19 = 679,
	S32V234_IMCR_VIU0_D20 = 645,
	S32V234_IMCR_VIU1_D20 = 680,
	S32V234_IMCR_VIU0_D21 = 646,
	S32V234_IMCR_VIU1_D21 = 681,
	S32V234_IMCR_VIU0_D22 = 647,
	S32V234_IMCR_VIU1_D22 = 682,
	S32V234_IMCR_VIU0_D23 = 648,
	S32V234_IMCR_VIU1_D23 = 683,
	S32V234_IMCR_VIU0_D4 = 629,
	S32V234_IMCR_VIU0_D5 = 630,
	S32V234_IMCR_VIU0_D6 = 631,
	S32V234_IMCR_VIU0_D7 = 632,
	S32V234_IMCR_VIU0_D8 = 633,
	S32V234_IMCR_VIU1_D8 = 668,
	S32V234_IMCR_VIU0_D9 = 634,
	S32V234_IMCR_VIU1_D9 = 669,
	S32V234_IMCR_USDHC_DAT0 = 903,
	S32V234_IMCR_USDHC_DAT1 = 904,
	S32V234_IMCR_USDHC_DAT2 = 905,
	S32V234_IMCR_USDHC_DAT3 = 906,
	S32V234_IMCR_USDHC_DAT4 = 907,
	S32V234_IMCR_USDHC_DAT5 = 908,
	S32V234_IMCR_USDHC_DAT6 = 909,
	S32V234_IMCR_USDHC_DAT7 = 910,
	S32V234_IMCR_IIC0_DATA = 781,
	S32V234_IMCR_IIC1_DATA = 783,
	S32V234_IMCR_IIC2_DATA = 785,
	S32V234_IMCR_SIUL_EIRQ0 = 590,
	S32V234_IMCR_SIUL_EIRQ10 = 600,
	S32V234_IMCR_SIUL_EIRQ11 = 601,
	S32V234_IMCR_SIUL_EIRQ12 = 602,
	S32V234_IMCR_SIUL_EIRQ13 = 603,
	S32V234_IMCR_SIUL_EIRQ14 = 604,
	S32V234_IMCR_SIUL_EIRQ15 = 605,
	S32V234_IMCR_SIUL_EIRQ16 = 606,
	S32V234_IMCR_SIUL_EIRQ17 = 607,
	S32V234_IMCR_SIUL_EIRQ18 = 608,
	S32V234_IMCR_SIUL_EIRQ19 = 609,
	S32V234_IMCR_SIUL_EIRQ1 = 591,
	S32V234_IMCR_SIUL_EIRQ20 = 610,
	S32V234_IMCR_SIUL_EIRQ21 = 611,
	S32V234_IMCR_SIUL_EIRQ22 = 612,
	S32V234_IMCR_SIUL_EIRQ23 = 613,
	S32V234_IMCR_SIUL_EIRQ24 = 614,
	S32V234_IMCR_SIUL_EIRQ25 = 615,
	S32V234_IMCR_SIUL_EIRQ26 = 616,
	S32V234_IMCR_SIUL_EIRQ27 = 617,
	S32V234_IMCR_SIUL_EIRQ28 = 618,
	S32V234_IMCR_SIUL_EIRQ29 = 619,
	S32V234_IMCR_SIUL_EIRQ2 = 592,
	S32V234_IMCR_SIUL_EIRQ30 = 620,
	S32V234_IMCR_SIUL_EIRQ31 = 621,
	S32V234_IMCR_SIUL_EIRQ3 = 593,
	S32V234_IMCR_SIUL_EIRQ4 = 594,
	S32V234_IMCR_SIUL_EIRQ5 = 595,
	S32V234_IMCR_SIUL_EIRQ6 = 596,
	S32V234_IMCR_SIUL_EIRQ7 = 597,
	S32V234_IMCR_SIUL_EIRQ8 = 598,
	S32V234_IMCR_SIUL_EIRQ9 = 599,
	S32V234_IMCR_FlexTimer0_EXTCLK = 520,
	S32V234_IMCR_FlexTimer1_EXTCLK = 529,
	S32V234_IMCR_CAN_FD0_RXD = 700,
	S32V234_IMCR_CAN_FD1_RXD = 701,
	S32V234_IMCR_VIU0_HSYNC = 622,
	S32V234_IMCR_VIU1_HSYNC = 657,
	S32V234_IMCR_SSE_IN0 = 1018,
	S32V234_IMCR_SSE_IN1 = 1019,
	S32V234_IMCR_SSE_IN2 = 1020,
	S32V234_IMCR_SSE_IN3 = 1021,
	S32V234_IMCR_Ethernet_MDIO = 981,
	S32V234_IMCR_VIU0_PCLK = 624,
	S32V234_IMCR_VIU1_PCLK = 659,
	S32V234_IMCR_LFAST_REF_CLK = 550,
	S32V234_IMCR_UART0_RXD = 712,
	S32V234_IMCR_UART1_RXD = 714,
	S32V234_IMCR_Ethernet_RX_CLK = 979,
	S32V234_IMCR_Ethernet_RX_D0 = 974,
	S32V234_IMCR_Ethernet_RX_D1 = 975,
	S32V234_IMCR_Ethernet_RX_D2 = 976,
	S32V234_IMCR_Ethernet_RX_D3 = 977,
	S32V234_IMCR_Ethernet_RX_DV = 973,
	S32V234_IMCR_Ethernet_RX_ER = 970,
	S32V234_IMCR_SPI0_SCK = 801,
	S32V234_IMCR_SPI1_SCK = 804,
	S32V234_IMCR_SPI2_SCK = 807,
	S32V234_IMCR_SPI3_SCK = 810,
	S32V234_IMCR_SPI0_SIN = 800,
	S32V234_IMCR_SPI1_SIN = 803,
	S32V234_IMCR_SPI2_SIN = 806,
	S32V234_IMCR_SPI3_SIN = 809,
	S32V234_IMCR_Ethernet_TIMER0 = 982,
	S32V234_IMCR_Ethernet_TIMER1 = 983,
	S32V234_IMCR_Ethernet_TIMER2 = 984,
	S32V234_IMCR_Ethernet_TX_CLK = 978,
	S32V234_IMCR_VIU0_VSYNC = 623,
	S32V234_IMCR_VIU1_VSYNC = 658,
	S32V234_IMCR_USDHC_WP = 900,
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc s32v234_pinctrl_pads[] = {
	S32V_PINCTRL_PIN(S32V234_MSCR_PA0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PA15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PB15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PC15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PD15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PE15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PF15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PG15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PH15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PJ15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK6),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK7),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK8),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK9),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK10),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK11),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK12),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK13),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK14),
	S32V_PINCTRL_PIN(S32V234_MSCR_PK15),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL0),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL1),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL2),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL3),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL4),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL5),
	S32V_PINCTRL_PIN(S32V234_MSCR_PL8),

	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA0),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA1),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA2),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA3),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA4),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA5),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA6),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DATA7),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_A_DQS),
	S32V_PINCTRL_PIN(S32V234_IMCR_BOOT_BOOTMOD0),
	S32V_PINCTRL_PIN(S32V234_IMCR_BOOT_BOOTMOD1),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_B_DATA0),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_B_DATA1),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_B_DATA2),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_B_DATA3),
	S32V_PINCTRL_PIN(S32V234_IMCR_QSPI_B_DQS),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexRay_CA_RX),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexRay_CB_RX),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH0),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH0),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH1),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH1),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH2),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH2),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH3),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH3),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH4),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH4),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_CH5),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_CH5),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC0_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC1_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC2_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_CMD),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_COL),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_CRS),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI0_CS0),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI1_CS0),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI2_CS0),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI3_CS0),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D10),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D10),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D11),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D11),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D12),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D12),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D13),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D13),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D14),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D14),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D15),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D15),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D16),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D16),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D17),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D17),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D18),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D18),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D19),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D19),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D20),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D20),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D21),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D21),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D22),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D22),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D23),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D23),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D4),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D5),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D6),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D7),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D8),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D8),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_D9),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_D9),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT0),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT1),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT2),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT3),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT4),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT5),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT6),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_DAT7),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC0_DATA),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC1_DATA),
	S32V_PINCTRL_PIN(S32V234_IMCR_IIC2_DATA),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ0),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ10),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ11),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ12),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ13),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ14),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ15),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ16),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ17),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ18),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ19),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ1),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ20),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ21),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ22),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ23),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ24),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ25),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ26),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ27),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ28),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ29),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ2),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ30),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ31),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ3),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ4),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ5),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ6),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ7),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ8),
	S32V_PINCTRL_PIN(S32V234_IMCR_SIUL_EIRQ9),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer0_EXTCLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_FlexTimer1_EXTCLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_CAN_FD0_RXD),
	S32V_PINCTRL_PIN(S32V234_IMCR_CAN_FD1_RXD),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_HSYNC),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_HSYNC),
	S32V_PINCTRL_PIN(S32V234_IMCR_SSE_IN0),
	S32V_PINCTRL_PIN(S32V234_IMCR_SSE_IN1),
	S32V_PINCTRL_PIN(S32V234_IMCR_SSE_IN2),
	S32V_PINCTRL_PIN(S32V234_IMCR_SSE_IN3),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_MDIO),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_PCLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_PCLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_LFAST_REF_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_UART0_RXD),
	S32V_PINCTRL_PIN(S32V234_IMCR_UART1_RXD),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_D0),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_D1),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_D2),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_D3),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_DV),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_RX_ER),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI0_SCK),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI1_SCK),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI2_SCK),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI3_SCK),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI0_SIN),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI1_SIN),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI2_SIN),
	S32V_PINCTRL_PIN(S32V234_IMCR_SPI3_SIN),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_TIMER0),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_TIMER1),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_TIMER2),
	S32V_PINCTRL_PIN(S32V234_IMCR_Ethernet_TX_CLK),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU0_VSYNC),
	S32V_PINCTRL_PIN(S32V234_IMCR_VIU1_VSYNC),
	S32V_PINCTRL_PIN(S32V234_IMCR_USDHC_WP),
};

static struct s32v_pinctrl_soc_info s32v234_pinctrl_info = {
	.pins = s32v234_pinctrl_pads,
	.npins = ARRAY_SIZE(s32v234_pinctrl_pads),
};


static const struct of_device_id s32v234_pinctrl_of_match[] = {
	{
		.compatible = "fsl,s32v234-siul2",
		.data = (void *) PINCTRL_V1,
	},
	{
		.compatible = "fsl,s32v234-siul2-pinctrl",
		.data = (void *) PINCTRL_V2,
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, s32v234_pinctrl_of_match);

static int s32v234_pinctrl_probe(struct platform_device *pdev)
{
	enum s32v_pinctrl_version vers;
	const struct of_device_id *of_id =
		of_match_device(s32v234_pinctrl_of_match, &pdev->dev);

	vers = (enum s32v_pinctrl_version) of_id->data;

	return s32v_pinctrl_probe(pdev, &s32v234_pinctrl_info, vers);
}

static struct platform_driver s32v234_pinctrl_driver = {
	.driver = {
		.name = "s32v234-siul2-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = s32v234_pinctrl_of_match,
	},
	.probe = s32v234_pinctrl_probe,
	.remove = s32v_pinctrl_remove,
};

module_platform_driver(s32v234_pinctrl_driver);

MODULE_DESCRIPTION("Freescale S32V234 pinctrl driver");
MODULE_LICENSE("GPL v2");
