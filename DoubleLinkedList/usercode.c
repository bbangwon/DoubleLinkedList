#include<stdio.h>
#include<string.h>
#include<malloc.h>

#include "mylist.h"
#include "mybintree.h"

// USERDATA
typedef struct USERDATA
{
	//멤버 함수 포인터
	const char* (*GetKey)(void*);

	char szName[64];	//Key
	char szPhone[64];
} USERDATA;

const char* GetKeyFromUserData(USERDATA* pUser)
{
	return pUser->szName;
}

USERDATA* CreateUserData(const char* pszName, const char* pszPhone)
{
	//C++ 생성자 흉내
	USERDATA* pNewData = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewData, 0, sizeof(USERDATA));

	strcpy_s(pNewData->szName, sizeof(pNewData->szName), pszName);
	strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), pszPhone);

	pNewData->GetKey = GetKeyFromUserData;

	return pNewData;
}

void PrintList(LIST_INFO* pListData)
{
	printf("PrintList(): g_nSize: %d, g_pHead [%p], g_Tail[%p]\n", pListData->nSize, pListData->pHead, pListData->pTail);

	int i = 0;
	LNODE* pTmp = pListData->pHead;
	while (pTmp != NULL)
	{
		if (pTmp == pListData->pHead || pTmp == pListData->pTail)
			printf("[DUMMY]\n");
		else
		{
			USERDATA* pUser = pTmp->pData;
			printf("Index:%d  %s\n", i,
				pUser->GetKey(pUser));
			i++;
		}
		pTmp = pTmp->next;
	}
}

void PrintTreeNode(TNODE* pParent)
{
	if (pParent == NULL)
		return;

	PrintTreeNode(pParent->left);

	printf("[%p] %p, %s, [%p]\n",
		pParent->left,
		pParent, 
		((USERDATA*)pParent->pData)->szName, 
		pParent->right);

	PrintTreeNode(pParent->right);
}

void PrintTree(TREE_INFO* pTreeData)
{
	if (pTreeData == NULL)
		return;

	PrintTreeNode(pTreeData->pRoot);
}

void ListDemo()
{
	LIST_INFO userList01 = { 0 };
	InitList(&userList01);

	USERDATA* pNewData = CreateUserData("Youngil", "010-1234-1234");
	InsertAtTail(&userList01, pNewData);

	pNewData = CreateUserData("TEST", "010-1111-2222");
	InsertAtTail(&userList01, pNewData);

	LIST_INFO userList02 = { 0 };
	InitList(&userList02);

	USERDATA* pNewData2 = CreateUserData("Youngil2", "010-1234-1234");
	InsertAtTail(&userList02, pNewData2);

	pNewData2 = CreateUserData("TEST2", "010-1111-2222");
	InsertAtTail(&userList02, pNewData2);

	PrintList(&userList01);
	PrintList(&userList02);

	ReleaseList(&userList01);
	ReleaseList(&userList02);
}

void TreeDemo()
{
	TREE_INFO userTree01 = { 0 };

	USERDATA* pNewData = CreateUserData("5번 항목", "5");
	InsertTNode(&userTree01, pNewData);

	pNewData = CreateUserData("4번 항목", "4");
	InsertTNode(&userTree01, pNewData);

	pNewData = CreateUserData("7번 항목", "7");
	InsertTNode(&userTree01, pNewData);

	pNewData = CreateUserData("6번 항목", "6");
	InsertTNode(&userTree01, pNewData);

	pNewData = CreateUserData("8번 항목", "8");
	InsertTNode(&userTree01, pNewData);

	PrintTree(&userTree01);
	ReleaseTree(&userTree01);
}

int main(void)
{
	TreeDemo();
	return 0;
}