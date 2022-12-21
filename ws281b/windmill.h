/**
 * @file            windmill.h
 * @brief           Windmill LED light controller.
 * @author          Wu Chang
 * @copyright       (C)2022 WDR Team. All Rights Reserved.
 * @date            2022-12-21
 */
#pragma once



/**
 * @brief           Random seed.
 * @attention       Change this seed to different number to get different blade active order.
 */
#define WINDMILL_RANDOM_SEED            114514

/**
 * @brief           Timeout of a blade when it is active.
 */
#define WINDMILL_BLADE_TIMEOUT          2500

/**
 * @brief           How many pieces of a blade timeout cycle.
 * @attention       windmill_blade_timeout must divisible by this value.
 */
#define WINDMILL_CONTROL_GRANULARITY    50



/**
 * @brief           The ID of the Blade.
 */
enum Windmill_Blade_ID {
    Windmill_Blade_A,               /**< The blade A */
    Windmill_Blade_B,               /**< The blade B */
    Windmill_Blade_C,               /**< The blade C */
    Windmill_Blade_D,               /**< The blade D */
    Windmill_Blade_E,               /**< The blade E */

    Windmill_Blade_COUNT            /**< The blade count (The centre light) */
};



/**
 * @brief           Process the event loop of windmill blade event.
 */
void windmill_process_event();
/**
 * @brief           Send color changed event.
 */
void windmill_send_color_changed_event();

/**
 * @brief           Raise a windmill blade hit event.
 *
 * @param id        Which blade has been hit.
 */
void windmill_hit(enum Windmill_Blade_ID id);

/**
 * @brief           Init the windmill blade controller.
 */
void windmill_init();
