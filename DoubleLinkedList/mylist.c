#include<stdio.h>
#include<string.h>
#include<malloc.h>

#include "mylist.h"

void InitList(LIST_INFO *pListData)
{
	
	pListData->pHead = (LNODE*)malloc(sizeof(LNODE));
	pListData->pTail = (LNODE*)malloc(sizeof(LNODE));
	pListData->nSize = 0;

	memset(pListData->pHead, 0, sizeof(LNODE));
	memset(pListData->pTail, 0, sizeof(LNODE));

	pListData->pHead->next = pListData->pTail;
	pListData->pTail->prev = pListData->pHead;
}

int InsertBefore(LIST_INFO* pListData, LNODE* pDstNode, void* pParam)
{
	LNODE* pNewNode = malloc(sizeof(LNODE));
	memset(pNewNode, 0, sizeof(LNODE));

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
	LNODE* pNewNode = malloc(sizeof(LNODE));
	memset(pNewNode, 0, sizeof(LNODE));

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
	LNODE* pTmp = pListData->pHead->next;
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
	LNODE* pNode = FindNode(pListData, pszKey);

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
	LNODE* pTmp = pListData->pHead;

	while (pTmp != NULL)
	{
		LNODE* pDelete = pTmp;
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

LNODE* GetAt(LIST_INFO* pListData, int idx)
{
	int i = 0;
	LNODE* pTmp = pListData->pHead->next;
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

LNODE* FindNode(LIST_INFO* pListData, const char* pszKey)
{
	LNODE* pTmp = pListData->pHead->next;
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
