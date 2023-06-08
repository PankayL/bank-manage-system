#ifndef _MYSORT_H_
#define _MYSORT_H_

#include "idcard.h"

//最后操作时间排序
typedef struct sort {
	//标记
	//0表示未当过枢轴，1表示当过枢轴，-1表示链表首尾空结点
	int isFlag;
	//姓名
	char name[20];
	//身份证号
	char Idcard[20];
	//银行卡号
	char bankCard[20];
	//最后操作时间
	int yearMonthDay;
	int hourMinSec;
	char operationTime[30];
	//指向上一结点
	struct sort* previous;
	//指向下一结点
	struct sort* next;
}SNode, * MySortList;

void SortByName(IdcardList L);
void SortByTime(IdcardList L);
void QSort(MySortList L, MySortList low, MySortList high);
MySortList Partition(MySortList L, MySortList low, MySortList high);

#endif // !_MYSORT_H_

