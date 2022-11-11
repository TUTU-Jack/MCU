#ifndef _TASK_H_
#define _TASK_H_

/*
	非抢占式时间片轮转任务调度
	利用定时器，给每个任务一定的等待时间，当时间片到达时，执行该任务，但是一旦其中一个任务出现死循环，那么该任务就不会退出，就会出现任务阻塞
	还有一种情况就是任务执行的时间大于任务给定的时间片，该任务还未执行完毕，下一个任务的时间片到达时，也不会执行下一个任务，也会出现任务阻塞
	任务执行时间小于时间片时，就会出现一定的空闲时间（等待下一个任务的时间片到达之后才会执行下一个任务）
	
	重点
	1.任务等待时间片不宜过大，过大出现CPU空闲
	2.任务等待时间片不宜过小，过小出现任务阻塞
	3.任务执行时间不宜过长（或出现死循环），过长出现任务阻塞
*/



/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"
#include "LED.h"


/***********************************************Define******************************************/
//任务定义
typedef struct _TASK_COMPONENTS
{
	uint8_t	Run;			//任务运行标志 0-不运行 1-运行
	uint8_t Timer;			//计时器
	uint8_t ItvTime;		//任务运行间隔时间(其他任务执行时间之和）
	void (*TaskHook)(void);	//任务函数
}TASK_COMPONENTS;

//任务队列
static TASK_COMPONENTS TaskComps[] = 
{
	{0,10,10,TaskDisplayLED_R},
	{0,20,20,TaskDisplayLED_G},
	{0,30,30,TaskDisplayLED_B},
};

#define TASK_MAX	sizeof(TaskComps)/sizeof(TaskComps[0])



/***********************************************Fuction*****************************************/
void TaskRemarks();		//任务标志处理
void TaskProcess();		//任务处理函数

#endif