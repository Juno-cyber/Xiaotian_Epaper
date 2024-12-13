#include "myfreertos.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
    	HAL_UART_Receive_IT(&huart2, rxBuffer, RTX_BUFFER_SIZE);    // 接收成功后还要重新打开中断
    }
}




