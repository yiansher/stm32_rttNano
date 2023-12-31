#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "u8g2.h"
#include "hal_oled.h"
#include "rtthread.h"

uint8_t led_onoff = 1;
struct rt_semaphore sem_lock;
struct rt_semaphore sem_led, sem_screen;
#define D_T 1000
/**************************************************************/
#if 1
extern void PrintVarFormat(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, const uint8_t *font, short var);
void led_thread_entry(void *parm)
{
    // GPIO_PinState *parm_b = parm;
//    short *parm1 = parm;
//    u8g2_t u8g2; // 显示器初始化结构体
//    MD_OLED_RST_Set(); //显示器复位拉高
//    u8g2Init(&u8g2);   //显示器调用初始化函数
    rt_tick_t tick = rt_tick_get();
    while (1)
    {
        tick = rt_tick_get();
        rt_kprintf("[led_entry:%d]\r\n", rt_tick_get());
        rt_sem_take(&sem_led, RT_WAITING_FOREVER);
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, (GPIO_PinState)led_onoff);
        led_onoff ^= 1;
        rt_sem_release(&sem_lock);
        rt_sem_release(&sem_screen);
//        rt_kprintf("[led_leave:%d]\r\n", rt_tick_get());
        rt_thread_delay_until(&tick,D_T);
    }
}

void led_task(void)
{
}
#endif
/**************************************************************/
#if 1
void PrintVarFormat(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, const uint8_t *font, short var)
{
    char var_buff[100];
    u8g2_SetFontMode(u8g2, 1); /*字体模式选择*/
    u8g2_SetFontDirection(u8g2, 0); /*字体方向选择*/
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf); /*字库选择*/
    u8g2_DrawStr(u8g2, 24 * 0, 30, "L");
    u8g2_DrawStr(u8g2, 24 * 1, 30, "E");
    u8g2_DrawStr(u8g2, 24 * 2, 30, "D");
    u8g2_DrawStr(u8g2, 24 * 3, 30, ":");
    sprintf(var_buff, "%d", var);  //传递变量（十进制（占四格））
    u8g2_DrawStr(u8g2, 24 * 4, 30, var_buff);
    u8g2_SendBuffer(u8g2);
}
extern uint8_t *set;
    u8g2_t u8g2; // 显示器初始化结构体
void screen_thread_entry(void *parameter)
{
//    static rt_err_t result;

//    MD_OLED_RST_Set(); //显示器复位拉高
//    u8g2Init(&u8g2);   //显示器调用初始化函数

    // short *parm = parameter;
    rt_tick_t tick = rt_tick_get();
    while(1)
    {
        tick = rt_tick_get();
        rt_kprintf("[screen_entry:%d]\r\n", rt_tick_get());
        rt_sem_take(&sem_screen, RT_WAITING_FOREVER);
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        u8g2_ClearBuffer(&u8g2);
        PrintVarFormat(&u8g2, 60, 30, u8g2_font_inb24_mf, (short)led_onoff);
        rt_sem_release(&sem_lock);
        rt_sem_release(&sem_led);
//        rt_kprintf("[screen_leave:%d]\r\n", rt_tick_get());
        rt_thread_delay_until(&tick,D_T);

    }
}

void screen_task(void)
{
    MD_OLED_RST_Set(); //显示器复位拉高
    u8g2Init(&u8g2);   //显示器调用初始化函数
    #if 1
    rt_sem_init(&sem_lock, "lock",     1,      RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_led, "led",   1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_screen, "screen",     0,      RT_IPC_FLAG_FIFO);
    rt_thread_t tid1;
    tid1 = rt_thread_create("led", led_thread_entry, RT_NULL,
                            1024, 8, 1);
    RT_ASSERT(tid1 != RT_NULL);
    rt_thread_startup(tid1);
    rt_thread_t tid2;
    tid2 = rt_thread_create("screen", screen_thread_entry, RT_NULL,
                            1024, 7, 1);
    RT_ASSERT(tid2 != RT_NULL);
    rt_thread_startup(tid2);
    #endif
    #if 0
    static rt_timer_t timer1;
    static rt_timer_t timer2;
    /* 创建定时器1  周期定时器 */
    timer1 = rt_timer_create("timer1", led_thread_entry,
                             RT_NULL, 1000,
                             RT_TIMER_FLAG_PERIODIC);

    /* 启动定时器1 */
    if (timer1 != RT_NULL) rt_timer_start(timer1);

    /* 创建定时器2 单次定时器 */
    timer2 = rt_timer_create("timer2", screen_thread_entry,
                             RT_NULL,  1000,
                             RT_TIMER_FLAG_PERIODIC);

    /* 启动定时器2 */
    if (timer2 != RT_NULL) rt_timer_start(timer2);
    return ;
    #endif
}

#endif
