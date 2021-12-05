#ifndef _USER_CTRL_H
#define _USER_CTRL_H
#include "stm32f4xx.h"

typedef struct {//用户任务结构体
    void (*task_func)(uint32_t dt_ms);
    uint32_t run_time_ms;
    uint8_t start_flag;
    uint8_t end_flag;
}user_task_t;

typedef struct {//用户控制句柄
    uint8_t user_task_runing;//用户任务开始执行
    uint8_t user_task_end;//当前任务结束
    uint8_t user_breakout;//强制结束
}user_handle;

user_handle user_ctrl_handle;

void user_ctrl(void);

#endif
