#include "record.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bankcard.h"
#include "idcard.h"
#pragma warning(disable : 4996)

//初始化存取款记录单链表
//构造一个空的单链表
RecordList InitRecordList(RecordList L) {
	//生成新结点作为头节点，用头指针L指向头节点
	L = (RecordList)malloc(sizeof(RNode));
	//对结构体中的数据域进行初始化操作
	if (!L) {
		system("cls");
		printf("存取款信息单链表初始化失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//开户年月日、时分秒
		getTime(L);
		//头结点的指针域置空
		L->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		L->tail = L;
		//初始化标识符
		L->isFlag = 1;
		//存储当前总金额
		L->balance = 0.0;
		//结点个数
		L->count = 1;
	}
	return L;
}

//增加存取款记录单链表的结点
double addRNode(RecordList L, int isFlag) {
	//生成新结点 
	RecordList newNode = (RecordList)malloc(sizeof(RNode));
	RecordList middleTemp;
	/*对结点数据域和指针域进行赋值*/
	//存取金额
	double amountOfMoney = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                 金额：");
	scanf_s("%lf", &amountOfMoney);
	if (isFlag == 1) {
		if (amountOfMoney < 0) {
			amountOfMoney = -amountOfMoney;
		}
	}
	else {
		if (amountOfMoney > 0) {
			amountOfMoney = -amountOfMoney;
		}
		if ((amountOfMoney + L->balance) < 0) {
			system("cls");
			printf("余额不足！\n");
			system("pause");
			return L->balance;
		}
	}
	//对新结点的信息进行填充
	if (!newNode) {
		system("cls");
		printf("存取款信息单链表新结点添加失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//存取款记录金额、存取款后当前余额
		newNode->amountOfMoney = amountOfMoney;
		newNode->balance = L->balance + newNode->amountOfMoney;
		L->balance = newNode->balance;
		//存取款操作年月日、时分秒
		getTime(newNode);
		//初始化标识符
		newNode->isFlag = 1;
		//连接结点 
		middleTemp = L->tail;
		middleTemp->next = newNode;
		//尾结点的指针域置空
		newNode->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		L->tail = newNode;
		//增加结点个数
		L->count++;
	}
	//释放连接新结点时定义的过程结点所申请的空间
	//free(middleTemp);
	return L->balance;
}

//修改存取款记录单链表结点的数据
//仅有单条存取款信息被修改，但账户总额不变
void modifyRNode(RecordList L, double amountOfMoney, double balance, int yearMonthDay, int hourMinSec, char operationTime[]) {
	//存取款记录金额、存取款后当前余额
	L->amountOfMoney = amountOfMoney;
	L->balance = balance;
	//存取款操作年月日、时分秒
	L->yearMonthDay = yearMonthDay;
	L->yearMonthDay = yearMonthDay;
	L->hourMinSec = hourMinSec;
	//L->operationTime = operationTime;
}

//删除单条存取款信息
//仅在逻辑上删除单链表信息，在物理上仍旧存在，但此时只有管理员有权限查询
void deleteRNode(RecordList L) {
	L->isFlag = 0;
}


//删除全部存取款记录
//仅在逻辑上删除单链表信息，在物理上仍旧存在，但此时只有管理员有权限查询
void deleteRecordList(RecordList L) {
	L->isFlag = 0;
}

//输出存取款记录单链表各个结点存储的记录
int printRecordList(RecordList L) {
	L = L->next;
	if (L == NULL) {
		system("cls");
		printf("无记录！\n");
		return 0;
	}
	else {
		while (L != NULL) {
			printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", L->operationTime, L->amountOfMoney, L->balance);
			L = L->next;
		}
		return 1;
	}
	//free(temp);
}

//获取当前时间
//对结点的生成时间进行赋值
void getTime(RecordList L) {
	int year, month, day, hour, min, sec;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	year = p->tm_year + 1900;   //获取当前年份,从1900开始，所以要加1900
	month = p->tm_mon + 1;      //获取当前月份,范围是0-11,所以要加1
	day = p->tm_mday;           //获取当前月份日数,范围是1-31
	hour = p->tm_hour + 8;      //获取当前时, 这里获取西方的时间, 刚好相差八个小时
	min = p->tm_min;            //获取当前分
	sec = p->tm_sec;            //获取当前秒
	//使用sprintf整合字符串
	//sprintf(nowTime, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec);
	sprintf(L->operationTime, "%d-%02d-%02d-%02d:%02d:%02d", year, month, day, hour, min, sec);
	//对结点时间进行赋值
	L->year = year;
	L->month = month;
	L->day = day;
	L->yearMonthDay = year * 10000 + month * 100 + day;
	L->hourMinSec = hour * 10000 + min * 100 + sec;
}

//转账功能
double Transfer(IdcardList IdL, RecordList ReL) {
	char account[20];
	RecordList middleTemp;
	/*对结点数据域和指针域进行赋值*/
	//转账金额
	double amountOfMoney = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             银行卡：");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               金额：");
	scanf("%lf", &amountOfMoney);
	//查看目标卡是否存在
	int i;
	IdL = IdL->next;
	while (IdL != NULL) {
		for (i = 0; i < IdL->isFlag; i++) {
			if (strcmp(account, IdL->bankCards[i]->bankCard) == 0) {
				if (IdL->bankCards[i]->isFlag == 2) {
					system("cls");
					printf("该卡已注销！\n");
					system("pause");
					return ReL->balance;
				}
				break;
			}
			if (i == 3) {
				break;
			}
		}
		if (strcmp(account, IdL->bankCards[i]->bankCard) == 0) {
			break;
		}
		IdL = IdL->next;
	}
	if (IdL == NULL) {
		system("cls");
		printf("该卡不存在！\n");
		system("pause");
		return ReL->balance;
	}
	//判断当前卡余额是否充足
	if ((ReL->balance - amountOfMoney) < 0) {
		system("cls");
		printf("余额不足！\n");
		system("pause");
		return ReL->balance;
	}
	//转出卡生成新结点 
	RecordList newNode = (RecordList)malloc(sizeof(RNode));
	//转出卡增加记录结点
	//对新结点的信息进行填充
	if (!newNode) {
		system("cls");
		printf("存取款信息单链表新结点添加失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//存取款记录金额、存取款后当前余额
		newNode->amountOfMoney = 0;
		newNode->amountOfMoney -= amountOfMoney;
		newNode->balance = ReL->balance + newNode->amountOfMoney;
		ReL->balance = newNode->balance;
		//存取款操作年月日、时分秒
		getTime(newNode);
		//初始化标识符
		newNode->isFlag = 1;
		//连接结点 
		middleTemp = ReL->tail;
		middleTemp->next = newNode;
		//尾结点的指针域置空
		newNode->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		ReL->tail = newNode;
		//增加结点个数
		ReL->count++;
	}
	//释放连接新结点时定义的过程结点所申请的空间
	//free(middleTemp);

	//目标卡增加新结点
	RecordList target = (RecordList)malloc(sizeof(RNode));
	//转入卡增加记录结点
	//对新结点的信息进行填充
	if (!target) {
		system("cls");
		printf("存取款信息单链表新结点添加失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//存取款记录金额、存取款后当前余额
		target->amountOfMoney = amountOfMoney;
		target->balance = IdL->bankCards[i]->L->balance + newNode->amountOfMoney;
		IdL->bankCards[i]->L->balance = target->balance;
		//存取款操作年月日、时分秒
		getTime(target);
		//初始化标识符
		target->isFlag = 1;
		//连接结点 
		middleTemp = IdL->bankCards[i]->L->tail;
		middleTemp->next = target;
		//尾结点的指针域置空
		target->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		IdL->bankCards[i]->L->tail = target;
		//增加结点个数
		IdL->bankCards[i]->L->count++;
		//修改目标卡总额
		IdL->bankCards[i]->nowBalance = IdL->bankCards[i]->L->balance;
	}



	//转出卡总余额
	return ReL->balance;
}