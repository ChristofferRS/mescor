/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MIMXRT1176xxxxx
package_id: MIMXRT1176DVMAA
mcu_data: ksdk2_0
processor_version: 0.9.6
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: L13, peripheral: LPUART1, signal: TXD, pin_signal: GPIO_AD_24, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: M15, peripheral: LPUART1, signal: RXD, pin_signal: GPIO_AD_25, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 is configured as LPUART1_TXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_I2C_ConfigurePins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: N8, peripheral: LPI2C5, signal: SCL, pin_signal: GPIO_LPSR_05, software_input_on: Enable, pull_up_down_config: Pull_Up, pull_keeper_select: Keeper,
    open_drain: Enable, drive_strength: Normal, slew_rate: Slow}
  - {pin_num: N7, peripheral: LPI2C5, signal: SDA, pin_signal: GPIO_LPSR_04, software_input_on: Enable, pull_up_down_config: Pull_Up, pull_keeper_select: Keeper,
    open_drain: Enable, drive_strength: Normal, slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_I2C_ConfigurePins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_I2C_ConfigurePins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_04_LPI2C5_SDA,         /* GPIO_LPSR_04 is configured as LPI2C5_SDA */
      1U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_05_LPI2C5_SCL,         /* GPIO_LPSR_05 is configured as LPI2C5_SCL */
      1U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_04_LPI2C5_SDA,         /* GPIO_LPSR_04 PAD functional properties : */
      0x0AU);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull up
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_05_LPI2C5_SCL,         /* GPIO_LPSR_05 PAD functional properties : */
      0x0AU);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: normal driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull up
                                                 Open Drain LPSR Field: Enabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_FLEXIO_ConfigurePins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: R17, peripheral: FLEXIO2, signal: 'IO, 10', pin_signal: GPIO_AD_10, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: P16, peripheral: FLEXIO2, signal: 'IO, 11', pin_signal: GPIO_AD_11, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: P17, peripheral: FLEXIO2, signal: 'IO, 12', pin_signal: GPIO_AD_12, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: L12, peripheral: FLEXIO2, signal: 'IO, 13', pin_signal: GPIO_AD_13, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_FLEXIO_ConfigurePins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_FLEXIO_ConfigurePins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_10_FLEXIO2_D10,          /* GPIO_AD_10 is configured as FLEXIO2_D10 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_11_FLEXIO2_D11,          /* GPIO_AD_11 is configured as FLEXIO2_D11 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_12_FLEXIO2_D12,          /* GPIO_AD_12 is configured as FLEXIO2_D12 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_13_FLEXIO2_D13,          /* GPIO_AD_13 is configured as FLEXIO2_D13 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_10_FLEXIO2_D10,          /* GPIO_AD_10 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_11_FLEXIO2_D11,          /* GPIO_AD_11 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_12_FLEXIO2_D12,          /* GPIO_AD_12 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_13_FLEXIO2_D13,          /* GPIO_AD_13 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_SAI_ConfigurePins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: N15, peripheral: SAI1, signal: sai_mclk, pin_signal: GPIO_AD_17, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_SAI_ConfigurePins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_SAI_ConfigurePins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_17_SAI1_MCLK,            /* GPIO_AD_17 is configured as SAI1_MCLK */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_GPR->GPR0 = ((IOMUXC_GPR->GPR0 &
    (~(IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_MASK)))  /* Mask bits to zero which are setting */
      | IOMUXC_GPR_GPR0_SAI1_MCLK_DIR(0x01U)  /* SAI1_MCLK signal direction control: 0x01U */
    );
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_17_SAI1_MCLK,            /* GPIO_AD_17 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
