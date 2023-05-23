#include<stdio.h>
#include<string.h>
#include<malloc.h>

#include "mylist.h"

void InitList(LIST_INFO *pListData)
{
	
	pListData->pHead = (NODE*)malloc(sizeof(NODE));
	pListData->pTail = (NODE*)malloc(sizeof(NODE));
	pListData->nSize = 0;

	memset(pListData->pHead, 0, sizeof(NODE));
	memset(pListData->pTail, 0, sizeof(NODE));

	pListData->pHead->next = pListData->pTail;
	pListData->pTail->prev = pListData->pHead;
}

int InsertBefore(LIST_INFO* pListData, NODE* pDstNode, void* pParam)
{
	NODE* pNewNode = malloc(sizeof(NODE));
	memset(pNewNode, 0, sizeof(NODE));

	pNewNode->pData = pParam;

	pNewNode->prev = pDstNode->prev;
	pNewNode->next = pDstNode;

	pDstNode->prev = pNewNode;
	pNewNode->prev->next = pNewNode;

	pListData->nSize++;
	return pListData->nSize;
}

int InsertAtTail(LIST_INFO* pListData, void* pParam)
{
	return InsertBefore(pListData, pListData->pTail, pParam);
}

int InsertAtHead(LIST_INFO* pListData, void* pParam)
{
	NODE* pNewNode = malloc(sizeof(NODE));
	memset(pNewNode, 0, sizeof(NODE));

	//관리대상 자료에 관한 초기화 
	pNewNode->pData = pParam;

	//연결 리스트에 관한 초기화
	pNewNode->next = pListData->pHead->next;
	pNewNode->prev = pListData->pHead;

	pListData->pHead->next = pNewNode;
	pNewNode->next->prev = pNewNode;

	pListData->nSize++;
	return pListData->nSize;
}

int InsertAt(LIST_INFO* pListData, int idx, void* pParam)
{
	int i = 0;
	NODE* pTmp = pListData->pHead->next;
	while (pTmp != pListData->pTail)
	{
		if (i == idx)
		{
			InsertBefore(pListData, pTmp, pParam);
			return i;
		}

		pTmp = pTmp->next;
		++i;
	}

	InsertAtTail(pListData, pParam);
	++i;

	return i;
}

int DeleteNode(LIST_INFO* pListData, const char* pszKey)
{
	NODE* pNode = FindNode(pListData, pszKey);

	pNode->prev->next = pNode->next;
	pNode->next->prev = pNode->prev;

	pListData->nSize--;

	printf("DeleteNode(): [%p]\n", pNode);
	free(pNode->pData);
	free(pNode);
	return 0;
}


void ReleaseList(LIST_INFO* pListData)
{
	NODE* pTmp = pListData->pHead;

	while (pTmp != NULL)
	{
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("free(%p)\n", pDelete);

		free(pDelete->pData);
		free(pDelete);
	}

	pListData->pHead = NULL;
	pListData->pTail = NULL;
	pListData->nSize = 0;

	puts("ReleaseList()");
}

NODE* GetAt(LIST_INFO* pListData, int idx)
{
	int i = 0;
	NODE* pTmp = pListData->pHead->next;
	while (pTmp != pListData->pTail)
	{
		if (i == idx)
			return pTmp;

		pTmp = pTmp->next;
		++i;
	}
	return NULL;
}

int GetSize(LIST_INFO* pListData)
{
	return pListData->nSize;
}

int GetLength(LIST_INFO* pListData)
{
	return GetSize(pListData);
}

int IsEmpty(LIST_INFO* pListData)
{
	return GetSize(pListData);
}

NODE* FindNode(LIST_INFO* pListData, const char* pszKey)
{
	NODE* pTmp = pListData->pHead->next;
	const char* (*pfGetKey)(void*) = NULL;

	while (pTmp != pListData->pTail)
	{
		pfGetKey = pTmp->pData;	//C++ function vtable 흉내

		//C++ this pointer 흉내
		if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0)
			return pTmp;

		pTmp = pTmp->next;
	}

	return NULL;
}
