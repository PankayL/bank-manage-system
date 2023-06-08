#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "idcard.h"

enum {maxSize = 50, numCard = 4};

typedef struct searchNode {
	//ÿ��������洢����Ϣ
	//���֤�ţ��������п��ţ���Ӧ��Ϣ���ĵ�ַ
	char* idCard[maxSize];
	BankCard cards[maxSize][numCard];
	struct INode* nodeAdress[maxSize];
	//ָ����һ�����
	struct searchNode* next;
}searchNode, * searchList;

IdcardList findIdCard(IdcardList L);
BankCard findMyAccount(IdcardList L, char account[], char passward[]);
BankCard findInforAccount(IdcardList L, char account[]);
IdcardList findOwner(IdcardList L, char account[]);
void SearchByNameDate(IdcardList L);
void FuzzySearch(IdcardList L);
int KMP(char dstStr[], char modelStr[]);
void getNextArr(char modelStr[], int* next);

#endif // !_SEARCH_H_

