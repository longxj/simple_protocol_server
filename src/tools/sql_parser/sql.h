#ifndef __SQL_H
#define __SQL_H

struct SqlNodeType{
	int type;
	double dVal;
	char text[48];
	struct SqlNodeType *lpNext; // 指向同一层的节点
	struct SqlNodeType *lpSub;  // 指向子节点
};

void ProcessTree(struct SqlNodeType* pNode);
struct SqlNodeType* MallocNewNode();
struct SqlNodeType* FatherAddSon(struct SqlNodeType* pFather, struct SqlNodeType* pSon);
struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1);
struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1, struct SqlNodeType* pSon2);
struct SqlNodeType* NewFatherAddSon(int iType, struct SqlNodeType* pSon1, struct SqlNodeType* pSon2, struct SqlNodeType* pSon3);

#endif
