/**
 * @file            ws281b2.h
 * @brief           The adapter layer for ws281b driver.
 * @author          Wu Chang
 * @copyright       (C)2022 WDR Team. All Rights Reserved.
 * @date            2022-12-18
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief           The ID of the Port.
 */
enum WS2_Port_ID {
    WS2_Port_A,               /**< The port A */
    WS2_Port_B,               /**< The port B */
    WS2_Port_C,               /**< The port C */
    WS2_Port_D,               /**< The port D */
    WS2_Port_E,               /**< The port E */

    WS2_Port_COUNT            /**< The port count */
};

/**
 * @brief           The color of LED.
 */
struct WS2_Color {
    uint8_t G;                  /**< Green */
    uint8_t R;                  /**< Red */
    uint8_t B;                  /**< Blue */
};



/**
 * @brief           Set the arrows.
 *
 * @param port      Which port to control.
 * @param on        Set the port on / off.
 */
void WS2_set_arrows(enum WS2_Port_ID port, bool on);
/**
 * @brief           Set the surrounding.
 *
 * @param port      Which port to control.
 * @param on        Set the port on / off.
 */
void WS2_set_surrounding(enum WS2_Port_ID port, bool on);

/**
 * @brief           Init the buffers.
 */
void WS2_control_init();
/**
 * @brief           Set LED colors.
 * @attention       This function will be effect on the next WS2_set_xxx method.
 *
 * @param colorOn   The color of the LED on.
 * @param colorOff  The color of the LED off.
 */
void WS2_control_color(struct WS2_Color colorOn, struct WS2_Color colorOff);
/**
 * @brief           Send the buffer of the port.
 *
 * @param port      Which port to control.
 */
void WS2_control_send(enum WS2_Port_ID port);
