#include "sql.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct SqlNodeType* MallocNewNode()
{
	struct SqlNodeType* pNew = (struct SqlNodeType*)malloc(sizeof(struct SqlNodeType));
	if (!pNew)
	{
		return pNew;
	}
	memset(pNew, 0, sizeof(*pNew));			
	return pNew;
}
	
void ProcessTree(struct SqlNodeType* pNode)
{
	printf("Info: done.\n");
}

struct SqlNodeType* FatherAddSon(struct SqlNodeType* pFather, struct SqlNodeType* pSon)
{
	struct SqlNodeType* pFS = pFather->lpSub;
	if (!pFS)
	{
		pFather->lpSub = pSon;
		return pFather;
	}
	else
	{
		while(pFS->lpNext)
		{
			pFS = pFS->lpNext;
		}

		pFS->lpNext = pSon;
		return pFather;
	}
}

struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1)
{
	struct SqlNodeType* pFather = MallocNewNode();
	if (!pFather)
	{
		return pFather;
	}

	pFather->type = iType;

	FatherAddSon(pFather, pSon1);
	return pFather;
}

struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1, struct SqlNodeType* pSon2)
{
	struct SqlNodeType* pFather = MallocNewNode();
	if (!pFather)
	{
		return pFather;
	}

	pFather->type = iType;

	FatherAddSon(pFather, pSon1);
	FatherAddSon(pFather, pSon2);

	return pFather;
}

struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1, struct SqlNodeType* pSon2, struct SqlNodeType* pSon3)
{
	struct SqlNodeType* pFather = MallocNewNode();
	if (!pFather)
	{
		return pFather;
	}

	pFather->type = iType;

	FatherAddSon(pFather, pSon1);
	FatherAddSon(pFather, pSon2);
	FatherAddSon(pFather, pSon3);

	return pFather;
}

