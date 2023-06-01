#pragma once

typedef struct NODE
{
	void* pData;

	struct NODE* prev;
	struct NODE* next;
} NODE;