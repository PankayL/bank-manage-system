#include "record.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bankcard.h"
#include "idcard.h"
#pragma warning(disable : 4996)

//��ʼ����ȡ���¼������
//����һ���յĵ�����
RecordList InitRecordList(RecordList L) {
	//�����½����Ϊͷ�ڵ㣬��ͷָ��Lָ��ͷ�ڵ�
	L = (RecordList)malloc(sizeof(RNode));
	//�Խṹ���е���������г�ʼ������
	if (!L) {
		system("cls");
		printf("��ȡ����Ϣ�������ʼ��ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//���������ա�ʱ����
		getTime(L);
		//ͷ����ָ�����ÿ�
		L->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		L->tail = L;
		//��ʼ����ʶ��
		L->isFlag = 1;
		//�洢��ǰ�ܽ��
		L->balance = 0.0;
		//������
		L->count = 1;
	}
	return L;
}

//���Ӵ�ȡ���¼������Ľ��
double addRNode(RecordList L, int isFlag) {
	//�����½�� 
	RecordList newNode = (RecordList)malloc(sizeof(RNode));
	RecordList middleTemp;
	/*�Խ���������ָ������и�ֵ*/
	//��ȡ���
	double amountOfMoney = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                 ��");
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
			printf("���㣡\n");
			system("pause");
			return L->balance;
		}
	}
	//���½�����Ϣ�������
	if (!newNode) {
		system("cls");
		printf("��ȡ����Ϣ�������½�����ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//��ȡ���¼����ȡ���ǰ���
		newNode->amountOfMoney = amountOfMoney;
		newNode->balance = L->balance + newNode->amountOfMoney;
		L->balance = newNode->balance;
		//��ȡ����������ա�ʱ����
		getTime(newNode);
		//��ʼ����ʶ��
		newNode->isFlag = 1;
		//���ӽ�� 
		middleTemp = L->tail;
		middleTemp->next = newNode;
		//β����ָ�����ÿ�
		newNode->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		L->tail = newNode;
		//���ӽ�����
		L->count++;
	}
	//�ͷ������½��ʱ����Ĺ��̽��������Ŀռ�
	//free(middleTemp);
	return L->balance;
}

//�޸Ĵ�ȡ���¼�������������
//���е�����ȡ����Ϣ���޸ģ����˻��ܶ��
void modifyRNode(RecordList L, double amountOfMoney, double balance, int yearMonthDay, int hourMinSec, char operationTime[]) {
	//��ȡ���¼����ȡ���ǰ���
	L->amountOfMoney = amountOfMoney;
	L->balance = balance;
	//��ȡ����������ա�ʱ����
	L->yearMonthDay = yearMonthDay;
	L->yearMonthDay = yearMonthDay;
	L->hourMinSec = hourMinSec;
	//L->operationTime = operationTime;
}

//ɾ��������ȡ����Ϣ
//�����߼���ɾ����������Ϣ�����������Ծɴ��ڣ�����ʱֻ�й���Ա��Ȩ�޲�ѯ
void deleteRNode(RecordList L) {
	L->isFlag = 0;
}


//ɾ��ȫ����ȡ���¼
//�����߼���ɾ����������Ϣ�����������Ծɴ��ڣ�����ʱֻ�й���Ա��Ȩ�޲�ѯ
void deleteRecordList(RecordList L) {
	L->isFlag = 0;
}

//�����ȡ���¼������������洢�ļ�¼
int printRecordList(RecordList L) {
	L = L->next;
	if (L == NULL) {
		system("cls");
		printf("�޼�¼��\n");
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

//��ȡ��ǰʱ��
//�Խ�������ʱ����и�ֵ
void getTime(RecordList L) {
	int year, month, day, hour, min, sec;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	year = p->tm_year + 1900;   //��ȡ��ǰ���,��1900��ʼ������Ҫ��1900
	month = p->tm_mon + 1;      //��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1
	day = p->tm_mday;           //��ȡ��ǰ�·�����,��Χ��1-31
	hour = p->tm_hour + 8;      //��ȡ��ǰʱ, �����ȡ������ʱ��, �պ����˸�Сʱ
	min = p->tm_min;            //��ȡ��ǰ��
	sec = p->tm_sec;            //��ȡ��ǰ��
	//ʹ��sprintf�����ַ���
	//sprintf(nowTime, "%d-%d-%d %d:%d:%d", year, month, day, hour, min, sec);
	sprintf(L->operationTime, "%d-%02d-%02d-%02d:%02d:%02d", year, month, day, hour, min, sec);
	//�Խ��ʱ����и�ֵ
	L->year = year;
	L->month = month;
	L->day = day;
	L->yearMonthDay = year * 10000 + month * 100 + day;
	L->hourMinSec = hour * 10000 + min * 100 + sec;
}

//ת�˹���
double Transfer(IdcardList IdL, RecordList ReL) {
	char account[20];
	RecordList middleTemp;
	/*�Խ���������ָ������и�ֵ*/
	//ת�˽��
	double amountOfMoney = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             ���п���");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               ��");
	scanf("%lf", &amountOfMoney);
	//�鿴Ŀ�꿨�Ƿ����
	int i;
	IdL = IdL->next;
	while (IdL != NULL) {
		for (i = 0; i < IdL->isFlag; i++) {
			if (strcmp(account, IdL->bankCards[i]->bankCard) == 0) {
				if (IdL->bankCards[i]->isFlag == 2) {
					system("cls");
					printf("�ÿ���ע����\n");
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
		printf("�ÿ������ڣ�\n");
		system("pause");
		return ReL->balance;
	}
	//�жϵ�ǰ������Ƿ����
	if ((ReL->balance - amountOfMoney) < 0) {
		system("cls");
		printf("���㣡\n");
		system("pause");
		return ReL->balance;
	}
	//ת���������½�� 
	RecordList newNode = (RecordList)malloc(sizeof(RNode));
	//ת�������Ӽ�¼���
	//���½�����Ϣ�������
	if (!newNode) {
		system("cls");
		printf("��ȡ����Ϣ�������½�����ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//��ȡ���¼����ȡ���ǰ���
		newNode->amountOfMoney = 0;
		newNode->amountOfMoney -= amountOfMoney;
		newNode->balance = ReL->balance + newNode->amountOfMoney;
		ReL->balance = newNode->balance;
		//��ȡ����������ա�ʱ����
		getTime(newNode);
		//��ʼ����ʶ��
		newNode->isFlag = 1;
		//���ӽ�� 
		middleTemp = ReL->tail;
		middleTemp->next = newNode;
		//β����ָ�����ÿ�
		newNode->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		ReL->tail = newNode;
		//���ӽ�����
		ReL->count++;
	}
	//�ͷ������½��ʱ����Ĺ��̽��������Ŀռ�
	//free(middleTemp);

	//Ŀ�꿨�����½��
	RecordList target = (RecordList)malloc(sizeof(RNode));
	//ת�뿨���Ӽ�¼���
	//���½�����Ϣ�������
	if (!target) {
		system("cls");
		printf("��ȡ����Ϣ�������½�����ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//��ȡ���¼����ȡ���ǰ���
		target->amountOfMoney = amountOfMoney;
		target->balance = IdL->bankCards[i]->L->balance + newNode->amountOfMoney;
		IdL->bankCards[i]->L->balance = target->balance;
		//��ȡ����������ա�ʱ����
		getTime(target);
		//��ʼ����ʶ��
		target->isFlag = 1;
		//���ӽ�� 
		middleTemp = IdL->bankCards[i]->L->tail;
		middleTemp->next = target;
		//β����ָ�����ÿ�
		target->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		IdL->bankCards[i]->L->tail = target;
		//���ӽ�����
		IdL->bankCards[i]->L->count++;
		//�޸�Ŀ�꿨�ܶ�
		IdL->bankCards[i]->nowBalance = IdL->bankCards[i]->L->balance;
	}



	//ת���������
	return ReL->balance;
}