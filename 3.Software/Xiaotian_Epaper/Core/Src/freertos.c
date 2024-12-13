/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "EPAPER.h"
#include "myfreertos.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticEventGroup_t osStaticEventGroupDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for TASK_INIT */
osThreadId_t TASK_INITHandle;
const osThreadAttr_t TASK_INIT_attributes = {
  .name = "TASK_INIT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for TASK_SHOW */
osThreadId_t TASK_SHOWHandle;
const osThreadAttr_t TASK_SHOW_attributes = {
  .name = "TASK_SHOW",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TASK_RUN */
osThreadId_t TASK_RUNHandle;
const osThreadAttr_t TASK_RUN_attributes = {
  .name = "TASK_RUN",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TASK_READ */
osThreadId_t TASK_READHandle;
const osThreadAttr_t TASK_READ_attributes = {
  .name = "TASK_READ",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Timer_ds1302_read */
osTimerId_t Timer_ds1302_readHandle;
const osTimerAttr_t Timer_ds1302_read_attributes = {
  .name = "Timer_ds1302_read"
};
/* Definitions for Binary_Sem_1 */
osSemaphoreId_t Binary_Sem_1Handle;
const osSemaphoreAttr_t Binary_Sem_1_attributes = {
  .name = "Binary_Sem_1"
};
/* Definitions for Binary_Sem_2 */
osSemaphoreId_t Binary_Sem_2Handle;
const osSemaphoreAttr_t Binary_Sem_2_attributes = {
  .name = "Binary_Sem_2"
};
/* Definitions for Event_01 */
osEventFlagsId_t Event_01Handle;
osStaticEventGroupDef_t Event_01C;
const osEventFlagsAttr_t Event_01_attributes = {
  .name = "Event_01",
  .cb_mem = &Event_01C,
  .cb_size = sizeof(Event_01C),
};
/* Definitions for Event_02 */
osEventFlagsId_t Event_02Handle;
osStaticEventGroupDef_t Event_02C;
const osEventFlagsAttr_t Event_02_attributes = {
  .name = "Event_02",
  .cb_mem = &Event_02C,
  .cb_size = sizeof(Event_02C),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void task_init(void *argument);
void task_show(void *argument);
void task_run(void *argument);
void task_read(void *argument);
void Callback_ds1302_read(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of Binary_Sem_1 */
  Binary_Sem_1Handle = osSemaphoreNew(1, 1, &Binary_Sem_1_attributes);

  /* creation of Binary_Sem_2 */
  Binary_Sem_2Handle = osSemaphoreNew(1, 1, &Binary_Sem_2_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of Timer_ds1302_read */
  Timer_ds1302_readHandle = osTimerNew(Callback_ds1302_read, osTimerPeriodic, NULL, &Timer_ds1302_read_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of TASK_INIT */
  TASK_INITHandle = osThreadNew(task_init, NULL, &TASK_INIT_attributes);

  /* creation of TASK_SHOW */
  TASK_SHOWHandle = osThreadNew(task_show, NULL, &TASK_SHOW_attributes);

  /* creation of TASK_RUN */
  TASK_RUNHandle = osThreadNew(task_run, NULL, &TASK_RUN_attributes);

  /* creation of TASK_READ */
  TASK_READHandle = osThreadNew(task_read, NULL, &TASK_READ_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of Event_01 */
  Event_01Handle = osEventFlagsNew(&Event_01_attributes);

  /* creation of Event_02 */
  Event_02Handle = osEventFlagsNew(&Event_02_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_task_init */
/**
  * @brief  Function implementing the TASK_INIT thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_task_init */
void task_init(void *argument)
{
  /* USER CODE BEGIN task_init */
  /* Infinite loop */
  for(;;)
  {
    init();
  }
  /* USER CODE END task_init */
}

/* USER CODE BEGIN Header_task_show */
/**
* @brief Function implementing the TASK_SHOW thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_task_show */
void task_show(void *argument)
{
  /* USER CODE BEGIN task_show */
  /* Infinite loop */
  for(;;)
  {
    show();
  }
  /* USER CODE END task_show */
}

/* USER CODE BEGIN Header_task_run */
/**
* @brief Function implementing the TASK_RUN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_task_run */
void task_run(void *argument)
{
  /* USER CODE BEGIN task_run */
  /* Infinite loop */
  for(;;)
  {
    run();
  }
  /* USER CODE END task_run */
}

/* USER CODE BEGIN Header_task_read */
/**
* @brief Function implementing the TASK_READ thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_task_read */
void task_read(void *argument)
{
  /* USER CODE BEGIN task_read */
  /* Infinite loop */
  for(;;)
  {
    read();
  }
  /* USER CODE END task_read */
}

/* Callback_ds1302_read function */
void Callback_ds1302_read(void *argument)
{
  /* USER CODE BEGIN Callback_ds1302_read */

  /* USER CODE END Callback_ds1302_read */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

