#include "exti_task.h"
#include "ws281b2.h"
#include "windmill.h"
#include <stdbool.h>

extern uint16_t mode ;
void EXTI_A_Task(void)
{
    windmill_hit(Windmill_Blade_A);
}

void EXTI_B_Task(void)
{
    windmill_hit(Windmill_Blade_B);
}
void EXTI_C_Task(void)
{
    windmill_hit(Windmill_Blade_C);
}

void EXTI_D_Task(void)
{
    windmill_hit(Windmill_Blade_D);
}

void EXTI_E_Task(void)
{
    windmill_hit(Windmill_Blade_E);
}

void EXTI_reserve_Task(void)
{
    const struct WS2_Color color1 = {32, 172, 0};
    const struct WS2_Color color2 = {96, 0, 67};
    const struct WS2_Color colorOff = {0, 0, 0};

    static bool state = false;
    WS2_control_color((state ? color1 : color2), colorOff);
    state = !state;

    windmill_send_color_changed_event();
}
