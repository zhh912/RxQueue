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
		//printf("ͷָ���ڴ�������\r\n");
		return	FAILURE_USER;
	}
	//
	else
	{
		//printf("ͷָ���ڴ����ɹ���\r\n");
		rxChain->head	=	p;
	}
	//


	t	=	(struct	RXTEMPCHAINNODE*)malloc(sizeof(struct	RXTEMPCHAINNODE));
	if(t==NULL)
	{
		free(p);
		//printf("βָ���ڴ�������\r\n");
		return	FAILURE_USER;
	}
	//
	else
	{
		//printf("βָ���ڴ����ɹ���\r\n");
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
	printf("ͷָ��ĵ�ַ��		��%08X\r\n",p);
	printf("ͷָ���previous��ַ��	��%08X\r\n",p->previous);
	printf("ͷָ���next	��ַ��	��%08X\r\n",p->next);
	printf("ͷָ������ݳ��ȵ�ַ��	��%d\r\n",p->lengthOfData);
	printf("ͷָ���������ʼ��ַ��	��%08X\r\n",p->data);

	printf("********************************************\r\n\r\n");
#endif

	t->previous				=	p;
	t->next						=	NULL;
	t->lengthOfData		=	0;
	t->data						=	NULL;

#if	ENABLE_DEBUG_RXTEMPBUFFER
	printf("βָ��ĵ�ַ��		��%08X\r\n",t);
	printf("βָ���previous��ַ��	��%08X\r\n",t->previous);
	printf("βָ���next	��ַ��	��%08X\r\n",t->next);
	printf("βָ������ݳ��ȵ�ַ��	��%d\r\n",t->lengthOfData);
	printf("βָ���������ʼ��ַ��	��%08X\r\n",t->data);
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


	//�����æ��ֱ�ӷ��ط�æ��Ϣ��
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

	//��λ��æ��־λ
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

		//p��˫��ָ������
		p->previous			=	rxChain->head;
		p->next					=	ptr;

		//ǰ����������
		rxChain->head->next	=	p;
		ptr->previous				=	p;


		p->data						=	data;
		p->lengthOfData		=	len;
		
	}
	//

	//printf("�½��ڵ�ĵ�ַ��		��0x%08x\r\n",p);
	//printf("�½��ڵ��previous��ַ�ǣ�\t0x%08x\r\n",p->previous);
	//printf("�½��ڵ��next��ַ��	��\t0x%08x\r\n",p->next);
	//printf("�½��ڵ�����ݳ��ȵ�ַ�ǣ�%d\r\n",p->lengthOfData);
	//printf("�½��ڵ��data��ַ��	��\t0x%08x\r\n",p->data);

	//printf("********************************************\r\n\r\n");
#if	ENABLE_DEBUG_RXTEMPBUFFER
//��ӡ���нڵ�ĵ�ַ��Ϣ
	{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head;
		printf("������һ���ڵ㣡\r\n");
		do
		{
			printf("�ڵ�ĵ�ַ��		��0X%08X\r\n",ptr);
			printf("�ڵ��previous��ַ��	��0X%08X\r\n",ptr->previous);
			printf("�ڵ��next��ַ��	��0X%08X\r\n",ptr->next);
			printf("�ڵ�����ݳ��ȵ�ַ��	��%d\r\n",ptr->lengthOfData);
			printf("�ڵ��data��ַ��	��0X%08X\r\n",ptr->data);

			ptr	=	ptr->next;
			printf("\r\n");
		}while(ptr->next);//ֻҪ�ڵ����һ����ַ����0
		//
			printf("�ڵ�ĵ�ַ��		��0X%08X\r\n",ptr);
			printf("�ڵ��previous��ַ��	��0X%08X\r\n",ptr->previous);
			printf("�ڵ��next��ַ��	��0X%08X\r\n",ptr->next);
			printf("�ڵ�����ݳ��ȵ�ַ��	��%d\r\n",ptr->lengthOfData);
			printf("�ڵ��data��ַ��	��0X%08X\r\n",ptr->data);
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
	//��ȡ��Ϣ

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

		//�������ݲ㣬���ݳ��Ⱥ�ʵ������
		length	=	rxChain->tail->previous->lengthOfData;
		*len		=	length;
		memcpy(outputData,rxChain->tail->previous->data,length);


		//��������
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
//��ӡ���нڵ�ĵ�ַ��Ϣ
	{
		struct	RXTEMPCHAINNODE	*ptr;
		ptr	=	rxChain->head;
		printf("ɾ����һ���ڵ㣡\r\n");
		do
		{
			printf("�ڵ�ĵ�ַ��		��0X%08X\r\n",ptr);
			printf("�ڵ��previous��ַ��	��0X%08X\r\n",ptr->previous);
			printf("�ڵ��next��ַ��	��0X%08X\r\n",ptr->next);
			printf("�ڵ�����ݳ��ȵ�ַ��	��%d\r\n",ptr->lengthOfData);
			printf("�ڵ��data��ַ��	��0X%08X\r\n",ptr->data);

			ptr	=	ptr->next;
			printf("\r\n");
		}while(ptr->next);//ֻҪ�ڵ����һ����ַ����0
		//
			printf("�ڵ�ĵ�ַ��		��0X%08X\r\n",ptr);
			printf("�ڵ��previous��ַ��	��0X%08X\r\n",ptr->previous);
			printf("�ڵ��next��ַ��	��0X%08X\r\n",ptr->next);
			printf("�ڵ�����ݳ��ȵ�ַ��	��%d\r\n",ptr->lengthOfData);
			printf("�ڵ��data��ַ��	��0X%08X\r\n",ptr->data);
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
		
		/*�ͷ�rxChain��Tail�ڵ�*/
		//	free(ptr->previous);
			free(ptr->next);
			ptr->next	=	NULL;
			free(ptr->data);
			ptr->data	=	NULL;
			ptr->lengthOfData	=	0;
			free(ptr);
			ptr	=	NULL;

		/*�ͷ�rxChain����Ϣ���У�����head��tail�Ѿ��ͷŵ��ˣ�����Ҫ�ٴ�free*/
			rxChain->busy	=	0;
			rxChain->countOfNode	=	0;
			rxChain->maxCountOfNode	=	0;
			free(rxChain);
			rxChain	=	NULL;
		
		
			return	SUCCESS_USER;
		
}
//
