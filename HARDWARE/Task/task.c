#include "task.h"



/**************************************************************************************
* FunctionName : TaskRemarks()
* Description : 任务标志处理
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void TaskRemarks()
{
	uint8_t i;
	for(i = 0;i < TASK_MAX;i++)
	{
		if(TaskComps[i].Timer)
		{
			TaskComps[i].Timer--;
			if(TaskComps[i].Timer == 0)
			{
				TaskComps[i].Timer = TaskComps[i].ItvTime;
				TaskComps[i].Run = 1;
			}
		}
	}
}

/**************************************************************************************
* FunctionName : TaskProcess()
* Description : 任务处理
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void TaskProcess()
{
	uint8_t i;
	for(i = 0;i < TASK_MAX;i++)
	{
		if(TaskComps[i].Run)
		{
			TaskComps[i].Run = 0;
			TaskComps[i].TaskHook();
		}
	}
}