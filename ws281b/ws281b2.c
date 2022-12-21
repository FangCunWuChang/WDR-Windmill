/**
 * @file            ws281b2.c
 * @brief           The adapter layer for ws281b driver.
 * @author          Wu Chang
 * @copyright       (C)2022 WDR Team. All Rights Reserved.
 * @date            2022-12-20
 */

#include "ws281b2.h"
#include "ws281b.h"

#include <stdlib.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/**
 * @brief           The config information of a port.
 */
struct WS2_Port_Config {
    enum WS2_Port_ID        id;                         /**< The port id */
    TIM_HandleTypeDef*      handle;                     /**< The TIM handle */
    uint32_t                channel;                    /**< The TIM channel */
    int                     arrowsSize;                 /**< The size of arrows LED */
    int                     surroundingSize;            /**< The size of surrounding LED */
    bool                    arrowsOn : 1;               /**< The state of arrows LED */
    bool                    surroundingOn : 1;          /**< The state of surrounding LED */
};

/**
 * @brief       The config list of the ports
 */
static struct WS2_Port_Config WS2_port_config_list[WS2_Port_COUNT + 1] = {
        { WS2_Port_A, &htim1, TIM_CHANNEL_1,  207, 213, false, false },         /**< Port A0 */
        { WS2_Port_B, &htim1, TIM_CHANNEL_2,  209, 216, false, false },         /**< Port B0 */
        { WS2_Port_C, &htim3, TIM_CHANNEL_1,  204, 217, false, false },         /**< Port C1 */
        { WS2_Port_D, &htim1, TIM_CHANNEL_4,  205, 217, false, false },         /**< Port D0 */
        { WS2_Port_E, &htim3, TIM_CHANNEL_3,  202, 216, false, false },         /**< Port E1 */

        { WS2_Port_COUNT, &htim3, TIM_CHANNEL_4,  0, 100, true, true }         /**< Port Res1 */
};

/**
 * @brief       The color of LED on.
 */
static struct WS2_Color WS2_color_on = {0, 255, 0};
/**
 * @brief       The color of LED off.
 */
static struct WS2_Color WS2_color_off = {0, 0, 0};

/**
 * @brief       The data buffer of LED.
 */
static struct WS2_Color* WS2_port_buffer = NULL;

/* ---------------------------- public functions ------------------------------ */

void WS2_set_arrows(enum WS2_Port_ID port, bool on) {
    if (port > WS2_Port_COUNT) { return; }
    WS2_port_config_list[port].arrowsOn = on;
}

void WS2_set_surrounding(enum WS2_Port_ID port, bool on) {
    if (port > WS2_Port_COUNT) { return; }
    WS2_port_config_list[port].surroundingOn = on;
}


void WS2_control_init() {
    /** Get max LED size */
    int maxSize = 0;
    for (int i = 0; i < WS2_Port_COUNT + 1; i++) {
        int size = WS2_port_config_list[i].arrowsSize + WS2_port_config_list[i].surroundingSize;
        if (size > maxSize) {
            maxSize = size;
        }
    }

    /** Init port buffer */
    WS2_port_buffer = malloc(maxSize * sizeof(struct WS2_Color));
    for (int i = 0; i < maxSize; i++) {
        WS2_port_buffer[i] = WS2_color_off;
    }
}

void WS2_control_color(struct WS2_Color colorOn, struct WS2_Color colorOff) {
    WS2_color_on = colorOn;
    WS2_color_off = colorOff;
}

void WS2_control_send(enum WS2_Port_ID port) {
    if (port > WS2_Port_COUNT) { return; }

    /** Get the config of the port */
    TIM_HandleTypeDef*      handle                  =   WS2_port_config_list[port].handle;                     /**< The TIM handle */
    uint32_t                channel                 =   WS2_port_config_list[port].channel;                    /**< The TIM channel */
    int                     arrowsSize              =   WS2_port_config_list[port].arrowsSize;                 /**< The size of arrows LED */
    int                     surroundingSize         =   WS2_port_config_list[port].surroundingSize;            /**< The size of surrounding LED */
    bool                    arrowsOn                =   WS2_port_config_list[port].arrowsOn;                   /**< The state of arrows LED */
    bool                    surroundingOn           =   WS2_port_config_list[port].surroundingOn;              /**< The state of surrounding LED */

    /** Set surrounding buffer */
    for (int i = 0; i < surroundingSize; i++) {
        WS2_port_buffer[i] = surroundingOn ? WS2_color_on : WS2_color_off;
    }
    /** Set arrows buffer */
    for (int i = 0; i < arrowsSize; i++) {
        WS2_port_buffer[surroundingSize + i] = arrowsOn ? WS2_color_on : WS2_color_off;
    }

    /** Send data */
    WS_write_RGB((const void*)WS2_port_buffer, arrowsSize + surroundingSize, handle, channel);
}
