#include "alarm_system.h"
#include "led.h"
#include "buzzer.h"
#include "main.h"

# define LED_COUNT  4U   

#define MODE_STANDBY 0U
#define MODE_RUN     1U
#define MODE_ALARM   2U

void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
  uint16_t i = 0U; /* 循环计数变量 */

  /* if 判断：LED 编号只允许 1~4 */
  if (led_num > LED_COUNT)
  {
    return; /* return 直接结束当前函数 */
  }

  /* for 循环：初始化; 判断条件; 每次循环后执行 */
  for (i = 0U; i < times; i++)
  {
    led_on(led_num);          /* 点亮指定 LED */
    HAL_Delay(delay_ms);      /* 延时一段时间 */
    led_off(led_num);         /* 熄灭指定 LED */
    HAL_Delay(delay_ms);
  }
}

void beep(uint32_t beep_ms)
{
  buzzer_on();          /* 打开蜂鸣器 */
  HAL_Delay(beep_ms);   /* 保持响一段时间 */
  buzzer_off();         /* 关闭蜂鸣器 */
}

void alarm_sys_func(void)
{
    static uint8_t mode = MODE_STANDBY;
    uint8_t led_num = 0U;

    switch (mode)
    {
        case MODE_STANDBY:
            /* 待机：关闭所有 LED 和蜂鸣器 */
            for (led_num = 1U; led_num <= LED_COUNT; led_num++)
            {
                led_off(led_num);
            }

            buzzer_off();

            HAL_Delay(1000U);

            mode = MODE_RUN;
            break;

        case MODE_RUN:
            /* 运行：正常速度流水灯 */
            for (led_num = 1U; led_num <= LED_COUNT; led_num++)
            {
                blink_led(led_num, 1U, 300U);
            }

            mode = MODE_ALARM;
            break;

        case MODE_ALARM:
            /* 报警：快速流水灯 + 间隔蜂鸣 */
            for (led_num = 1U; led_num <= LED_COUNT; led_num++)
            {
                blink_led(led_num, 1U, 100U);

                beep(100U);
                HAL_Delay(100U);
            }

            mode = MODE_STANDBY;
            break;

        default:
            mode = MODE_STANDBY;
            break;
    }
}
