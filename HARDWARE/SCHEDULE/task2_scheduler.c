#include "task2_scheduler.h"
#include "led.h"
#include "uart.h"


void Loop_1000Hz(void){//执行周期1ms
    printf("周期1ms验证成功");
}

void Loop_500Hz(void){//执行周期2ms
    printf("周期2ms验证成功");
}

void Loop_100Hz(void){//执行周期10ms
    printf("周期10ms验证成功");
}

void Loop_50Hz(void){//执行周期20ms
    printf("周期20ms验证成功");

}

void Loop_10Hz(void){//执行周期100ms
    led_switch();
}

//系统任务配置，创建不同执行频率的“线程”
static sched_task_t sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_100Hz , 100,  0, 0},
	{Loop_50Hz  ,  50,  0, 0},
	{Loop_10Hz  ,  10,  0, 0},
};

#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))//利用宏设置线程数量
#define SECOND_MS 1000

void scheduler_setup(void){
    int index = 0;
    for (index=0; index < TASK_NUM; index++)
    {
        sched_tasks[index].interval_ticks = SECOND_MS/sched_tasks[index].rate_hz;
        if (sched_tasks[index].interval_ticks < 1)//最短周期1ms
        {
            sched_tasks[index].interval_ticks = 1;
        }
        
    }
}
/**********************************************************************************************************
*函 数 名: scheduler_run
*功能说明: 时分调度功能，根据所设定的执行时间执行相关功能
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void scheduler_run(void){
    int index = 0;
    for (index=0; index < TASK_NUM; index++)
    {
        uint32_t time_now = SysTick_GetTick();//获取系统当前时间，单位ms
        if (time_now - sched_tasks[index].last_run > sched_tasks[index].interval_ticks)
        {
            sched_tasks[index].last_run = time_now;
            sched_tasks[index].task_func();
        }
        
    }
    
}


