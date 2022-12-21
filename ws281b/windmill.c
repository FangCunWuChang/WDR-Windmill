/**
 * @file            windmill.c
 * @brief           Windmill LED light controller.
 * @author          Wu Chang
 * @copyright       (C)2022 WDR Team. All Rights Reserved.
 * @date            2022-12-21
 */

#include "windmill.h"
#include "ws281b2.h"
#include "stm32h7xx_hal.h"

#include <stdbool.h>
#include <stdlib.h>

enum Windmill_Blade_State;

static void windmill_blade_output(enum Windmill_Blade_ID id, enum Windmill_Blade_State state);

/* ------------------------------ private functions ---------------------------- */

/**
 * @brief           Loop counter struct.
 */
struct Windmill_Loop_Counter {
    int count;                    /**< Current loop count */
    int max_count;                /**< Target loop count */
};

/**
 * @brief               Init a loop counter.
 *
 * @param counter       Which counter you want to init.
 * @param max_count     The target count.
 */
static void windmill_loop_counter_init(struct Windmill_Loop_Counter* counter, const int max_count) {
    if (counter == NULL) { return; }

    counter->count = 0;
    counter->max_count = max_count;
}
/**
 * @brief               Add one count to a counter.
 *
 * @param counter       Which counter you want to add count.
 *
 * @return              Return true if the count reach the target count.
 */
static bool windmill_loop_counter_add(struct Windmill_Loop_Counter* counter) {
    if (counter == NULL) { return false; }

    counter->count += 1;
    if (counter->count >= counter->max_count) { counter->count = 0; }

    return counter->count == 0;
}
/**
 * @brief               Reset count to 0 of a counter.
 *
 * @param counter       Which counter you want to reset.
 */
static void windmill_loop_counter_reset(struct Windmill_Loop_Counter* counter) {
    if (counter == NULL) { return; }
    counter->count = 0;
}
/**
 * @brief               Check a counter if the count reach the target count.
 *
 * @param counter       Which counter you want to check.
 *
 * @return              Return true if the count reach the target count.
 */
static bool windmill_loop_counter_check(struct Windmill_Loop_Counter* counter) {
    if (counter == NULL) { return false; }
    return counter->count == 0;
}

/**
 * @brief               Windmill blade states.
 */
enum Windmill_Blade_State {
    Windmill_Blade_State_Off,          /**< Windmill blade is off */
    Windmill_Blade_State_Active,       /**< Windmill blade is active */
    Windmill_Blade_State_On            /**< Windmill blade is on */
};

/**
 * @brief           The states list of the five windmill blades.
 */
static enum Windmill_Blade_State windmill_state_list[Windmill_Blade_COUNT] = { Windmill_Blade_State_Off };
/**
 * @brief           The loop counter of the active blade.
 */
static struct Windmill_Loop_Counter windmill_current_active_loop_counter = {0, 0};

/**
 * @brief           Find the active blade.
 *
 * @param list      The blade state list.
 *
 * @return          Return the active blade id. If can't find an active blade, then return Windmill_Blade_COUNT + 1.
 */
static enum Windmill_Blade_ID windmill_find_active_blade(const enum Windmill_Blade_State* list) {
    if (list == NULL) { return Windmill_Blade_COUNT + 1; }

    for (int i = 0; i < Windmill_Blade_COUNT; i++){
        if (list[i] == Windmill_Blade_State_Active) { return i; }
    }
    return Windmill_Blade_COUNT + 1;
}

/**
 * @brief           Find a blade to active.
 *
 * @param list      The blade state list.
 *
 * @return          Return the blade id to active.
 *                  If can't find a blade to active or a blade is already active, then return Windmill_Blade_COUNT + 1.
 */
static enum Windmill_Blade_ID windmill_find_next_active_blade(const enum Windmill_Blade_State* list) {
    if (list == NULL) { return Windmill_Blade_COUNT + 1; }

    /** Find all off blade */
    int off_blade_count = 0;
    for (int i = 0; i < Windmill_Blade_COUNT; i++){
        if (list[i] == Windmill_Blade_State_Off) { off_blade_count++; }
    }
    if (off_blade_count == 0) { return Windmill_Blade_COUNT + 1; }

    /** Decide which blade to active */
    int next_blade_id = rand() % off_blade_count;
    for (int i = 0, j = 0; i < Windmill_Blade_COUNT && j < off_blade_count ; i++) {
        if (list[i] == Windmill_Blade_State_Off) {
            if (j == next_blade_id) { return i; }
            j++;
        }
    }

    return Windmill_Blade_COUNT + 1;
}

/**
 * @brief               Set the blade state.
 *
 * @param list          The blade state list.
 * @param id            Which blade you want to set.
 * @param state         Which state you want to set the blade into.
 */
static void windmill_set_blade_state(enum Windmill_Blade_State* list, enum Windmill_Blade_ID id, enum Windmill_Blade_State state) {
    if (list == NULL) { return; }
    if (id >= Windmill_Blade_COUNT) { return; }

    list[id] = state;
    windmill_blade_output(id, state);
}
/**
 * @brief               Get the blade state.
 *
 * @param list          The blade state list.
 * @param id            Which blade you want to get.
 *
 * @return              Return the state of the blade. If error, return Windmill_Blade_State_Off.
 */
static enum Windmill_Blade_State windmill_get_blade_state(enum Windmill_Blade_State* list, enum Windmill_Blade_ID id) {
    if (list == NULL) { return Windmill_Blade_State_Off; }
    if (id >= Windmill_Blade_COUNT) { return Windmill_Blade_State_Off; }
    return list[id];
}

/**
 * @brief               Check whether all blades are on.
 *
 * @param list          The blade state list.
 *
 * @return              Return true if all blades are on.
 */
static bool windmill_is_all_blade_on(const enum Windmill_Blade_State* list) {
    if (list == NULL) { return false; }

    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        if (list[i] != Windmill_Blade_State_On) { return false; }
    }
    return true;
}
/**
 * @brief               Check whether all blades are off.
 *
 * @param list          The blade state list.
 *
 * @return              Return false if not all blades are off.
 */
static bool windmill_is_all_blade_off(const enum Windmill_Blade_State* list) {
    if (list == NULL) { return true; }

    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        if (list[i] != Windmill_Blade_State_Off) { return false; }
    }
    return true;
}
/**
 * @brief               Turn off all blades.
 *
 * @param list          The blade state list.
 */
static void windmill_set_all_blade_off(enum Windmill_Blade_State* list) {
    if (list == NULL) { return; }
    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        windmill_set_blade_state(list, i, Windmill_Blade_State_Off);
    }
}

/**
 * @brief           Blade hit event buffer.
 */
static bool windmill_hit_buffer[Windmill_Blade_COUNT] = { false };
/**
 * @brief           Reset blade hit buffer.
 *
 * @param buffer    The blade hit buffer.
 */
static void windmill_hit_buffer_reset(bool* buffer) {
    if (buffer == NULL) { return; }
    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        buffer[i] = false;
    }
}

/**
 * @brief           Color changed flag.
 */
 static bool windmill_color_changed_flag = false;

 /**
  * @brief          Process color changed event.
  */
 static void windmill_process_color_changed_event() {
     if (windmill_color_changed_flag) {
         /** Send color for centre */
         windmill_blade_output(Windmill_Blade_COUNT, Windmill_Blade_State_On);

         /** Reset flag */
         windmill_color_changed_flag = false;
     }
 }

/* ---------------------------- public functions ------------------------------ */

void windmill_process_event() {
    /** Counter add 1 */
    windmill_loop_counter_add(&windmill_current_active_loop_counter);

    /** Check hit blade */
    bool active_blade_hit = false;
    bool other_blade_hit = false;
    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        if (windmill_hit_buffer[i]) {
            if (windmill_get_blade_state(windmill_state_list, i) == Windmill_Blade_State_Active) {
                active_blade_hit = true;
            }
            else {
                other_blade_hit = true;
            }
        }
    }
    /** Reset hit buffer */
    windmill_hit_buffer_reset(windmill_hit_buffer);

    /** Cheat - Uncomment to cheat. */
    double per = 0.8;
    int cheatCount = WINDMILL_CONTROL_GRANULARITY * per;
    other_blade_hit = false;
    active_blade_hit = (windmill_current_active_loop_counter.count >= cheatCount);

    if ((!windmill_is_all_blade_on(windmill_state_list)) && (active_blade_hit || other_blade_hit)) {    /**< Got a hit */
        if (active_blade_hit) {
            /** Set current blade On */
            windmill_set_blade_state(windmill_state_list,
                                     windmill_find_active_blade(windmill_state_list),
                                     Windmill_Blade_State_On);

            /** Active a blade */
            windmill_set_blade_state(windmill_state_list,
                                     windmill_find_next_active_blade(windmill_state_list),
                                     Windmill_Blade_State_Active);
        }
        else {
            /** Reset all blades */
            windmill_set_all_blade_off(windmill_state_list);

            /** Active a blade */
            windmill_set_blade_state(windmill_state_list,
                                     windmill_find_next_active_blade(windmill_state_list),
                                     Windmill_Blade_State_Active);
        }
        /** Process color changed event */
        windmill_process_color_changed_event();

        /** Reset counter */
        windmill_loop_counter_reset(&windmill_current_active_loop_counter);
    }
    else {                                                                                                  /**< Without a hit */
        /** If counter reached target */
        if (windmill_loop_counter_check(&windmill_current_active_loop_counter)) {
            /** If all on */
            if (windmill_is_all_blade_on(windmill_state_list)) {
                /** Reset all blades */
                windmill_set_all_blade_off(windmill_state_list);
                windmill_set_all_blade_off(windmill_state_list);
            }

            /** Get next blade */
            enum Windmill_Blade_ID next = windmill_find_next_active_blade(windmill_state_list);

            /** Reset all blades */
            windmill_set_all_blade_off(windmill_state_list);
            windmill_set_all_blade_off(windmill_state_list);

            /** Active a blade */
            windmill_set_blade_state(windmill_state_list, next, Windmill_Blade_State_Active);

            /** Process color changed event */
            windmill_process_color_changed_event();

            /** Reset counter */
            windmill_loop_counter_reset(&windmill_current_active_loop_counter);
        }
    }

    /** Delay until the next event loop cycle */
    HAL_Delay(WINDMILL_BLADE_TIMEOUT / WINDMILL_CONTROL_GRANULARITY);
}

void windmill_send_color_changed_event() {
    windmill_color_changed_flag = true;
}

void windmill_hit(enum Windmill_Blade_ID id) {
    if (id >= Windmill_Blade_COUNT) { return; }
    windmill_hit_buffer[id] = true;
}

void windmill_init() {
    /** Init the port */
    WS2_control_init();

    /** Set start color */
    const struct WS2_Color color1 = {32, 172, 0};
    __attribute__((unused)) const struct WS2_Color color2 = {96, 0, 67};
    const struct WS2_Color colorOff = {0, 0, 0};
    WS2_control_color(color1, colorOff);

    /** Close all blade */
    for (int i = 0; i < Windmill_Blade_COUNT; i++) {
        WS2_control_send((int)i);
    }
    HAL_Delay(WINDMILL_BLADE_TIMEOUT / WINDMILL_CONTROL_GRANULARITY);

    /** Init random */
    srand(WINDMILL_RANDOM_SEED);

    /** Init hit buffer */
    for (int i = 0; i < Windmill_Blade_COUNT ; i++) {
        windmill_hit_buffer[i] = false;
    }
    /** Init blade state list */
    for (int i = 0; i < Windmill_Blade_COUNT ; i++) {
        windmill_state_list[i] = Windmill_Blade_State_Off;
    }
    /** Init loop counter */
    windmill_loop_counter_init(&windmill_current_active_loop_counter, WINDMILL_CONTROL_GRANULARITY);

    /** Active a blade */
    windmill_set_blade_state(windmill_state_list,
                             windmill_find_next_active_blade(windmill_state_list),
                             Windmill_Blade_State_Active);
}

/* --------------------------------- interfaces ------------------------------- */

/**
 * @brief               Output a blade's LED state.
 *
 * @param id            Which blade you want to output.
 * @param state         What state you want to output.
 */
static void windmill_blade_output(enum Windmill_Blade_ID id, enum Windmill_Blade_State state) {
    if (id > Windmill_Blade_COUNT) { return; }

    /** Firstly close all LED */
    WS2_set_surrounding((int)id, false);
    WS2_set_arrows((int)id, false);

    /** Then turn on the LED */
    if (state >= Windmill_Blade_State_On) {
        WS2_set_surrounding((int)id, true);
    }
    if (state >= Windmill_Blade_State_Active) {
        WS2_set_arrows((int)id, true);
    }

    /** Then send data */
    WS2_control_send((int)id);
}
