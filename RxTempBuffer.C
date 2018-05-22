/**
  ******************************************************************************
  * @file    RxTempBuffer.c
  * @author  Alex-BNS	ZhaoHui
  * @version V1.0.0
  * @date    23-July-2017
  * @brief   
  * 
  ******************************************************************************
  *	@attention
  *	
  *	THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  *	WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  *	TIME. AS A RESULT, AUTHER SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT 
	*	OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING  FROM THE CONTENT 
	*	OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION 
	*	CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *	
  *	<h2><center>&copy; COPYRIGHT 2017 Alex-BNS	</center></h2>
  ******************************************************************************
  */
#include "RxTempBuffer.h"


/*
*********************************************************************************
*********************************************************************************
*/
unsigned	char	RxTempChainInit(struct	RXTEMPLIST *rxChain,unsigned	short	count)
{
	struct	RXTEMPCHAINNODE	*p,*t;


	p	=	(struct	RXTEMPCHAINNODE*)malloc(sizeof(struct	RXTEMPCHAINNODE));
	if(p==NULL)
	{
		//printf("头指针内存分配错误！\r\n");
		return	FAILURE_USER;
	}
	//
	else
	{
		//printf("头指针内存分配成功！\r\n");
		rxChain->head	=	p;
	}
	//


	t	=	(struct	RXTEMPCHAINNODE*)malloc(sizeof(struct	RXTEMPCHAINNODE));
	if(t==NULL)
	{
		free(p);
		//printf("尾指针内存分配错误！\r\n");
		return	FAILURE_USER;
	}
	//
	else
	{
		//printf("尾指针内存分配成功！\r\n");
		rxChain->tail	=	t;
	}
	//
	rxChain->maxCountOfNode	=	count;
	rxChain->busy						=	BUSY_USER;
	rxChain->countOfNode		=	0;

	p->previous				=	NULL;
	p->next						=	t;
	p->lengthOfData		=	0;
	p->data						=	NULL;

#if	ENABLE_DEBUG_RXTEMPBUFFER
	printf("头指针的地址是		：%08X\r\n",p);
	printf("头指针的previous地址是	：%08X\r\n",p->previous);
	printf("头指针的next	地址是	：%08X\r\n",p->next);
	printf("头指针的数据长度地址是	：%d\r\n",p->lengthOfData);
	printf("头指针的数据起始地址是	：%08X\r\n",p->data);

	printf("********************************************\r\n\r\n");
#endif

	t->previous				=	p;
	t->next						=	NULL;
	t->lengthOfData		=	0;
	t->data						=	NULL;

#if	ENABLE_DEBUG_RXTEMPBUFFER
	printf("尾指针的地址是		：%08X\r\n",t);
	printf("尾指针的previous地址是	：%08X\r\n",t->previous);
	printf("尾指针的next	地址是	：%08X\r\n",t->next);
	printf("尾指针的数据长度地址是	：%d\r\n",t->lengthOfData);
	printf("尾指针的数据起始地址是	：%08X\r\n",t->data);
	printf("********************************************\r\n\r\n");
#endif

	rxChain->busy						=	LEISURE_USER;
	//exit(EXIT_SUCCESS);
	return SUCCESS_USER;
}
//
//
unsigned	short	RxTempChainEmptyOrNot(struct	RXTEMPLIST *rxChain)
{
	return	rxChain->countOfNode;
}
//
//
unsigned	char	RxTempChainWrite(struct	RXTEMPLIST *rxChain,unsigned	char *rxData,unsigned	int len)
{
	struct	RXTEMPCHAINNODE	*p;
	unsigned	char	*data;


	//如果繁忙，直接返回繁忙信息。
	if(rxChain->busy	==	BUSY_USER)
	{
		return BUSY_USER;
	}
	//

	if(len	==	0)
	{
		rxChain->busy	=	LEISURE_USER;
		return	SUCCESS_USER;
	}
	//

	//置位繁忙标志位
	rxChain->busy	=	BUSY_USER;

	if(rxChain->countOfNode	==	rxChain->maxCountOfNode)
	{
		rxChain->busy	=	LEISURE_USER;
		return	FULL_USER;
	}
	//

	


	data	=	(unsigned	char*)malloc(sizeof(unsigned	char)*len);
	if(NULL	==	data)
	{
		rxChain->busy	=	LEISURE_USER;		
		return	FAILURE_USER;
	}
	//
	memcpy(data,rxData,len);

	p		=	(struct	RXTEMPCHAINNODE *)malloc(sizeof(struct	RXTEMPCHAINNODE));

	if(NULL	==	p)
	{
		free(data);
		rxChain->busy	=	LEISURE_USER;		
		return	FAILURE_USER;
	}
	//
	else
	{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head->next;

		//p的双向指针设置
		p->previous			=	rxChain->head;
		p->next					=	ptr;

		//前后链的设置
		rxChain->head->next	=	p;
		ptr->previous				=	p;


		p->data						=	data;
		p->lengthOfData		=	len;
		
	}
	//

	//printf("新建节点的地址是		：0x%08x\r\n",p);
	//printf("新建节点的previous地址是：\t0x%08x\r\n",p->previous);
	//printf("新建节点的next地址是	：\t0x%08x\r\n",p->next);
	//printf("新建节点的数据长度地址是：%d\r\n",p->lengthOfData);
	//printf("新建节点的data地址是	：\t0x%08x\r\n",p->data);

	//printf("********************************************\r\n\r\n");
#if	ENABLE_DEBUG_RXTEMPBUFFER
//打印所有节点的地址信息
	{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head;
		printf("加入了一个节点！\r\n");
		do
		{
			printf("节点的地址是		：0X%08X\r\n",ptr);
			printf("节点的previous地址是	：0X%08X\r\n",ptr->previous);
			printf("节点的next地址是	：0X%08X\r\n",ptr->next);
			printf("节点的数据长度地址是	：%d\r\n",ptr->lengthOfData);
			printf("节点的data地址是	：0X%08X\r\n",ptr->data);

			ptr	=	ptr->next;
			printf("\r\n");
		}while(ptr->next);//只要节点的下一个地址不是0
		//
			printf("节点的地址是		：0X%08X\r\n",ptr);
			printf("节点的previous地址是	：0X%08X\r\n",ptr->previous);
			printf("节点的next地址是	：0X%08X\r\n",ptr->next);
			printf("节点的数据长度地址是	：%d\r\n",ptr->lengthOfData);
			printf("节点的data地址是	：0X%08X\r\n",ptr->data);
			printf("\r\n");
			printf("\r\n");
	}
	//
#endif


	(rxChain->countOfNode)++;
	
	
	rxChain->busy	=	LEISURE_USER;

	return	SUCCESS_USER;
}
//



unsigned	char	RxTempChainRead(struct	RXTEMPLIST *rxChain,unsigned	char *outputData,unsigned int *len)
{
	if(rxChain->busy	==	BUSY_USER)
	{
		return BUSY_USER;
	}
	//

	rxChain->busy	=	BUSY_USER;
	//获取信息

	if(RxTempChainEmptyOrNot(rxChain)	==	EMPTY_USER)
	{
		rxChain->busy	=	LEISURE_USER;
		return EMPTY_USER;
	}
	//
	else
	{
		unsigned	int	length	=	0;
		struct	RXTEMPCHAINNODE		*ptr;

		//拷贝数据层，数据长度和实际数据
		length	=	rxChain->tail->previous->lengthOfData;
		*len		=	length;
		memcpy(outputData,rxChain->tail->previous->data,length);


		//更新链表
		ptr	=	rxChain->tail->previous;

		rxChain->tail->previous	=	ptr->previous;
		ptr->previous->next			=	rxChain->tail;

		ptr->lengthOfData				=	0;


		free(ptr->data);
		ptr->data	=	NULL;

		free(ptr);
		ptr				=	NULL;

	}
	//



	(rxChain->countOfNode)--;
	rxChain->busy	=	LEISURE_USER;

	
#if	ENABLE_DEBUG_RXTEMPBUFFER
//打印所有节点的地址信息
	{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head;
		printf("删除了一个节点！\r\n");
		do
		{
			printf("节点的地址是		：0X%08X\r\n",ptr);
			printf("节点的previous地址是	：0X%08X\r\n",ptr->previous);
			printf("节点的next地址是	：0X%08X\r\n",ptr->next);
			printf("节点的数据长度地址是	：%d\r\n",ptr->lengthOfData);
			printf("节点的data地址是	：0X%08X\r\n",ptr->data);

			ptr	=	ptr->next;
			printf("\r\n");
		}while(ptr->next);//只要节点的下一个地址不是0
		//
			printf("节点的地址是		：0X%08X\r\n",ptr);
			printf("节点的previous地址是	：0X%08X\r\n",ptr->previous);
			printf("节点的next地址是	：0X%08X\r\n",ptr->next);
			printf("节点的数据长度地址是	：%d\r\n",ptr->lengthOfData);
			printf("节点的data地址是	：0X%08X\r\n",ptr->data);
			printf("\r\n");
			printf("\r\n");
	}
	//
#endif
	
	
	return SUCCESS_USER;
}
//
unsigned	char	RxTempChainDel(struct	RXTEMPLIST *rxChain)
{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head;
		
		if(rxChain->busy	==	BUSY_USER)
		{
			return BUSY_USER;
		}
	
	
	
	
		free(ptr->previous);
		ptr->previous	=	NULL;
		while(ptr->next)
		{
			struct	RXTEMPCHAINNODE	*secondNode;
			secondNode	=	ptr->next;
			
			//free(ptr->previous);
			//free(ptr->next);
			free(ptr->data);
			ptr->data	=	NULL;
			ptr->lengthOfData	=	0;
			free(ptr);
			
			ptr	=	NULL;
			ptr	=	secondNode;
		}
		//
		
		/*释放rxChain的Tail节点*/
		//	free(ptr->previous);
			free(ptr->next);
			ptr->next	=	NULL;
			free(ptr->data);
			ptr->data	=	NULL;
			ptr->lengthOfData	=	0;
			free(ptr);
			ptr	=	NULL;

		/*释放rxChain的消息队列，其中head和tail已经释放掉了，不需要再次free*/
			rxChain->busy	=	0;
			rxChain->countOfNode	=	0;
			rxChain->maxCountOfNode	=	0;
			free(rxChain);
			rxChain	=	NULL;
		
		
			return	SUCCESS_USER;
		
}
//

