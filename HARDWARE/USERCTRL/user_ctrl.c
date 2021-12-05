#include "user_ctrl.h"
#include "led.h"
#include "delay.h"
#include "uart.h"

#define USER_TASK_NUM 3

void hello_master(void){
    printf("Hello Master!");
    delay_ms(100);
}
void wait_ctrl(void){//LED常亮等待命令
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_RESET);
}

static user_task_t user_tasks[USER_TASK_NUM]={//开机后自动执行
    {hello_master,1000,0,0},
    {led_switch,2000,0,0},
    {wait_ctrl,60000,0,0}
};

//顺序执行用户任务
static uint8_t index = 0;//用于记录正在执行的任务
static uint32_t running_time = 0;//任务已运行时间

void user_ctrl(void){
    if(user_ctrl_handle.user_task_runing){
        if(index < USER_TASK_NUM){
            if (running_time == 0)
            {
                user_tasks[index].start_flag = 1;
            }
            if (user_tasks[index].start_flag)
            {
                running_time = SysTick_GetTick();
                user_tasks[index].task_func();
                running_time = SysTick_GetTick()-running_time;
            }
            if (user_tasks[index].end_flag)
            {
                index ++;
                user_tasks[index].end_flag = 0;
                running_time = 0;
            }
            if (user_ctrl_handle.user_breakout)//任务强制结束
            {
                index ++;
                user_ctrl_handle.user_breakout = 0;
            }
            if (running_time > user_tasks[index].run_time_ms)
            {
                user_tasks[index].start_flag = 0;
                user_tasks[index].end_flag = 1;
            }
        }else {
            user_ctrl_handle.user_task_runing = 0;
            index = 0;
            running_time = 0;
        }
    }
}


