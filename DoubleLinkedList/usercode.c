#include<stdio.h>
#include<string.h>
#include<malloc.h>

#include "mylist.h"

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
	NODE* pTmp = pListData->pHead;
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


int main(void)
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
	return 0;
}