#pragma once

typedef struct TNODE
{
	void* pData;

	struct TNODE* left;
	struct TNODE* right;
} TNODE;

typedef struct TREE_INFO
{
	TNODE* pRoot;
	int	  nSize;
} TREE_INFO;

void ReleaseTree(TREE_INFO* pTreeData);
int InsertTNode(TREE_INFO* pListData, void* pParam);
TNODE* FindTNode(TREE_INFO* pListData, const char* pszKey);
int DeleteTNode(TREE_INFO* pListData, const char* pszKey);
