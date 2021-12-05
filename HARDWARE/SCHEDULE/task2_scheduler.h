#ifndef _TASK2_SCHEDULER_H
#define _TASK2_SCHEDULER_H
#include "stm32f4xx.h"

//实现时分调度器结构体
typedef struct
{
void(*task_func)(void);
uint16_t rate_hz;
uint16_t interval_ticks;
uint32_t last_run;
}sched_task_t;



void scheduler_setup(void);
void scheduler_run(void);





#endif

