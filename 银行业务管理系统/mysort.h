#ifndef _MYSORT_H_
#define _MYSORT_H_

#include "idcard.h"

//������ʱ������
typedef struct sort {
	//���
	//0��ʾδ�������ᣬ1��ʾ�������ᣬ-1��ʾ������β�ս��
	int isFlag;
	//����
	char name[20];
	//���֤��
	char Idcard[20];
	//���п���
	char bankCard[20];
	//������ʱ��
	int yearMonthDay;
	int hourMinSec;
	char operationTime[30];
	//ָ����һ���
	struct sort* previous;
	//ָ����һ���
	struct sort* next;
}SNode, * MySortList;

void SortByName(IdcardList L);
void SortByTime(IdcardList L);
void QSort(MySortList L, MySortList low, MySortList high);
MySortList Partition(MySortList L, MySortList low, MySortList high);

#endif // !_MYSORT_H_

