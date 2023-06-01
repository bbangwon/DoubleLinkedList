#include<stdio.h>
#include<string.h>
#include<malloc.h>

#include "mybintree.h"

int _InsertRecursiveTNode(TNODE* pRootNode, TNODE *newNode)
{
	const char* (*pfGetKey)(void*) = NULL;

	pfGetKey = *(int*) pRootNode->pData;
	const char* rootKey = pfGetKey(pRootNode->pData);

	pfGetKey = *(int*) newNode->pData;
	const char* newKey = pfGetKey(newNode->pData);

	if (strcmp(rootKey, newKey) > 0)	//왼쪽으로
	{
		if (pRootNode->left == NULL)
		{
			pRootNode->left = newNode;
			return 0;
		}

		//왼쪽
		return _InsertRecursiveTNode(pRootNode->left, newNode);
	}
	else
	{
		if (pRootNode->right == NULL)
		{
			pRootNode->right = newNode;
			return 0;
		}

		//오른쪽
		return _InsertRecursiveTNode(pRootNode->right, newNode);
	}

	return 1;
}

int InsertTNode(TREE_INFO* pTreeData, void* pParam)
{
	TNODE* pNewNode = malloc(sizeof(TNODE));
	memset(pNewNode, 0, sizeof(TNODE));

	pNewNode->pData = pParam;

	TNODE* pTmp = pTreeData->pRoot;
	const char* (*pfGetKey)(void*) = NULL;

	pfGetKey = *(int*)pNewNode->pData;
	const char* newKey = pfGetKey(pNewNode->pData);


	//반복문 방식
	if (pTmp == NULL)
	{
		pTreeData->pRoot = pNewNode;
		pTreeData->nSize++;
		return 0;
	}

	while (pTmp != NULL)
	{
		pfGetKey = *(int*)pTmp->pData;
		const char* rootKey = pfGetKey(pTmp->pData);

		if (strcmp(rootKey, newKey) > 0)	//rootKey - newKey값 > 0 => newKey가 작은 값
		{
			if (pTmp->left == NULL)
			{
				pTmp->left = pNewNode;
				pTreeData->nSize++;
				return 0;
			}
			else
			{
				pTmp = pTmp->left;
				continue;
			}
		}
		else
		{
			if (pTmp->right == NULL)
			{
				pTmp->right = pNewNode;
				pTreeData->nSize++;
				return 0;
			}
			else
			{
				pTmp = pTmp->right;
				continue;
			}
		}
	}

	//재귀호출 방식
	//if(_InsertRecursiveTNode(pTreeData->pRoot, pNewNode) == 0)
	//{
	//	pTreeData->nSize++;
	//	return 0;
	//}
	return 1;
}

TNODE* FindTNode(TREE_INFO* pTreeData, const char* pszKey)
{
	return NULL;
}

int DeleteTNode(TREE_INFO* pTreeData, const char* pszKey)
{
	return 0;
}

void _ReleaseTreeNode(TNODE* pParent)
{
	if (pParent == NULL)
		return;

	_ReleaseTreeNode(pParent->left);
	_ReleaseTreeNode(pParent->right);

	printf("free(): [%p]\n", pParent);
	free(pParent);
}

void ReleaseTree(TREE_INFO* pTreeData)
{
	_ReleaseTreeNode(pTreeData->pRoot);
	pTreeData->pRoot = NULL;
	pTreeData->nSize = 0;
}



