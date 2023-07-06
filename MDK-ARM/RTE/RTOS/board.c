/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "main.h"
#include "usart.h"


//extern void HAL_Init(void);
extern void SystemClock_Config(void);
extern void SystemCoreClockUpdate(void);
extern void MX_USART2_UART_Init(void);;

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (30*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_os_tick_callback(void)
{
    rt_interrupt_enter();
    
    rt_tick_increase();

    rt_interrupt_leave();
}

void SysTick_Handler(void)
{
    rt_os_tick_callback();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
//#error "TODO 1: OS Tick Configuration."
    /* 
     * TODO 1: OS Tick Configuration
     * Enable the hardware timer and call the rt_os_tick_callback function
     * periodically with the frequency RT_TICK_PER_SECOND. 
     */
  HAL_Init(); // ��ʼ�� HAL ��
  SystemClock_Config(); // ����ϵͳʱ��
  SystemCoreClockUpdate(); // ��ϵͳʱ�ӽ��и���

//  /* 2��OS Tick Ƶ�����ã�RT_TICK_PER_SECOND = 1000 ��ʾ 1ms ����һ���ж� */
//  SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE

static int uart_init(void)
{
//#error "TODO 2: Enable the hardware uart and config baudrate."
    MX_USART2_UART_Init();
    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&huart2);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&huart2, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&huart2, (uint8_t *)(str + i), 1, 1);
    }
}
char rt_hw_console_getchar(void)
{
int ch = -1;

    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
    {
        ch = huart2.Instance->DR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&huart2);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}
#endif

