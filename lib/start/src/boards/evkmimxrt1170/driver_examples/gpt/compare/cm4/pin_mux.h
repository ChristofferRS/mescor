/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* GPIO_AD_24 (coord L13), LPUART1_TXD/J31[2] */
/* Routed pin properties */
#define BOARD_INITDEBUG_UARTPINS_LPUART1_TXD_PERIPHERAL                  LPUART1   /*!< Peripheral name */
#define BOARD_INITDEBUG_UARTPINS_LPUART1_TXD_SIGNAL                          TXD   /*!< Signal name */

/* GPIO_AD_25 (coord M15), LPUART1_RXD/J32[2] */
/* Routed pin properties */
#define BOARD_INITDEBUG_UARTPINS_LPUART1_RXD_PERIPHERAL                  LPUART1   /*!< Peripheral name */
#define BOARD_INITDEBUG_UARTPINS_LPUART1_RXD_SIGNAL                          RXD   /*!< Signal name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);          /* Function assigned for the Cortex-M7F */

/* GPIO_AD_02 (coord R13), SIM1_RST/J57[5]/J44[C2]/LCD_RST_B/J48[21]/J25[11]/J10[6] */
/* Routed pin properties */
#define BOARD_INITGPTPINS_SIM1_RST_PERIPHERAL                               GPT2   /*!< Peripheral name */
#define BOARD_INITGPTPINS_SIM1_RST_SIGNAL                            gpt_compare   /*!< Signal name */
#define BOARD_INITGPTPINS_SIM1_RST_CHANNEL                                    1U   /*!< Signal channel */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitGptPins(void);                 /* Function assigned for the Cortex-M7F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/