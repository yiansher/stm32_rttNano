#include "app_timer.h"
// #include "app_uart.h"

// static void led_alive(void * parm)
// {
// //    char *str = (char*)parm;
//     static int i = 0;
//     if(i==0)
//     led_write(LED0_PIN, PIN_HIGH);
//     else
//     led_write(LED0_PIN, PIN_LOW);
//     i=1-i;
// //    APP_TRACE("%s",str);
// }


timer_counter_t timer_counters[1] =
{
    {500, CNT_0, NO_FUNC, "1s counter", NULL}
};


static void timer_counter_plusplus(timer_counter_t *timer_counter_list)
{
    uint8_t i = 0;

    for(i = 0; i < TC_NUM; i++)
    {
        if(timer_counter_list[i].flag & FLAG_SET)
            continue;

        timer_counter_list[i].cnt += 1;

        if(timer_counter_list[i].cnt < timer_counter_list[i].delay_time)
            continue;
        else
        {
            if(! (timer_counter_list[i].flag & IS_FUNC) )
                timer_counter_list[i].flag |= 0x01;
            else
            {
                void (*cbFunction)(const char *) = (void (*)(const char *))timer_counter_list[i].cbFunction;
                cbFunction(timer_counter_list[i].tcName);
            }

            timer_counter_list[i].cnt = 0;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim-> Instance == htim6.Instance)
    {
        timer_counter_plusplus(timer_counters);
    }
}

