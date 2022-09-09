#include "FreeRTOS.h"
#include "task.h"

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
portCHAR flag1;
portCHAR flag2;

#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];

//����������
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;

//����������ƿ�
TCB_t Task1TCB;
TCB_t Task2TCB;

/* �����ʱ */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}


/* ����1 */
void Task1_Entry( void *p_arg )
{
	for( ;; )
	{
		flag1 = 1;
		delay( 100 );		
		flag1 = 0;
		delay( 100 );
		
		/* �����л����������ֶ��л� */
        taskYIELD();
	}
}


/* ����2 */
void Task2_Entry( void *p_arg )
{
	for( ;; )
	{
		flag2 = 1;
		delay( 100 );		
		flag2 = 0;
		delay( 100 );
		
		/* �����л����������ֶ��л� */
        taskYIELD();
	}
}


int main(void)
{
	prvInitialiseTaskLists();
	
	//��������
	Task1_Handle=xTaskCreateStatic(Task1_Entry,"Task1",TASK1_STACK_SIZE,NULL,Task1Stack,&Task1TCB);
	Task2_Handle=xTaskCreateStatic(Task2_Entry,"Task2",TASK2_STACK_SIZE,NULL,Task2Stack,&Task2TCB);
	
	//������ڵ���ӵ���Ӧ����������б�Ķ�Ӧ���ڵ���
	vListInsertEnd( &( pxReadyTasksLists[1] ), &( ((TCB_t *)(&Task1TCB))->xStateListItem ) );
	vListInsertEnd( &( pxReadyTasksLists[2] ), &( ((TCB_t *)(&Task2TCB))->xStateListItem ) );
//	vListInsertEnd(&(pxReadyTasksLists[1]),&(Task1TCB.xStateListItem));
//	vListInsertEnd(&(pxReadyTasksLists[2]),&(Task2TCB.xStateListItem));
	
	/* ��������������ʼ��������ȣ������ɹ��򲻷��� */
   vTaskStartScheduler(); 
	for(;;)
	{}
}
