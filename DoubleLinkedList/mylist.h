#pragma once

typedef struct LNODE
{
	void* pData;

	struct LNODE* prev;
	struct LNODE* next;
} LNODE;

typedef struct LIST_INFO
{
	LNODE* pHead;
	LNODE* pTail;
	int	  nSize;
} LIST_INFO;

void InitList(LIST_INFO* pListData);
void ReleaseList(LIST_INFO* pListData);
int InsertAtHead(LIST_INFO* pListData, void* pParam);
int InsertBefore(LIST_INFO* pListData, LNODE* pDstNode, void* pParam);
int InsertAtTail(LIST_INFO* pListData, void* pParam);
LNODE* FindNode(LIST_INFO* pListData, const char* pszKey);
int DeleteNode(LIST_INFO* pListData, const char* pszKey);
int GetSize(LIST_INFO* pListData);
int GetLength(LIST_INFO* pListData);
int IsEmpty(LIST_INFO* pListData);
int InsertAt(LIST_INFO* pListData, int idx, void* pParam);
LNODE* GetAt(LIST_INFO* pListData, int idx);
