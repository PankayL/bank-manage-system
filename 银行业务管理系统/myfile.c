#include "myfile.h"
#include <stdlib.h>
#include <stdio.h>
#include "record.h"
#include "bankcard.h"
#include "idcard.h"
#pragma warning(disable : 4996)

//��ȡ�ļ�
void ReadFile(IdcardList L) {
	FILE* fpIdList;		//��ȡ�ͻ������Ϣ
	FILE* fpBankList;	//��ȡ�ͻ����п���Ϣ
	FILE* fpRecordList;	//��ȡ�ͻ��Ĵ�ȡ���¼
	//����Ԥ���� 
	if ((fpIdList = fopen("IdCards.txt", "r")) == NULL) {
		printf("IdCards file open error!\n");
		exit(0);
	}
	if ((fpBankList = fopen("BankCards.txt", "r")) == NULL) {
		printf("BankCards file open error!\n");
		exit(0);
	}
	if ((fpRecordList = fopen("Records.txt", "r")) == NULL) {
		printf("Records file open error!\n");
		exit(0);
	}
	//ָ�������Ϣ��������һ����㣬���ڴ洢
	IdcardList last = L;
	int count;
	fscanf(fpIdList, "%d", &L->count);
	int readCount = 0;
	int i;
	while (feof(fpIdList) == 0) {
		IdcardList temp = (IdcardList)malloc(sizeof(INode));
		//��ȡ�ͻ������Ϣ
		fscanf(fpIdList, "%s %s %s %s %s %s %d", &temp->name, &temp->sex, &temp->nationality, 
			&temp->idCard, &temp->mobileTelephone, &temp->contactAddress, &temp->isFlag);
		//��ȡ�ÿͻ������п���Ϣ
		for (i = 0; i < temp->isFlag; i++) {
			//��ȡ�ͻ���Ӧ�����п���Ϣ
			BankCard myBank = (BankCard)malloc(sizeof(BankCardNode));
			fscanf(fpBankList, "%s %s %lf %d", &myBank->bankCard, &myBank->passward, &myBank->nowBalance, &myBank->isFlag);
			temp->bankCards[i] = myBank;
			//��ȡÿ�����п��Ĵ�ȡ���¼
			//��ȡÿ�����п���ȡ������ͷ�����Ϣ
			RecordList recTemp = (RecordList)malloc(sizeof(RNode));
			fscanf(fpRecordList, "%lf %s %d %d", &recTemp->balance, &recTemp->operationTime, &recTemp->isFlag, &recTemp->count);
			/*printf("%f %s %d %d\n", recTemp->balance, recTemp->operationTime, recTemp->isFlag, recTemp->count);
			printf("*****************");
			system("pause");*/
			temp->bankCards[i]->L = recTemp;
			temp->bankCards[i]->L->tail = recTemp;
			temp->bankCards[i]->L->tail->next = NULL;
			//��ȡÿ�����п��Ĵ�ȡ����Ϣ
			int j;
			for (j = 1; j < recTemp->count; j++) {
				/*char ch;
				ch = fgetc(fpRecordList);
				printf("%d**********\n", ch);*/
				RecordList tempRec = (RecordList)malloc(sizeof(RNode));
				fscanf(fpRecordList, "%lf %lf %d %d %d %d %d %s %d", &tempRec->amountOfMoney, &tempRec->balance,
					&tempRec->year, &tempRec->month, &tempRec->day, &tempRec->yearMonthDay, &tempRec->hourMinSec,
					&tempRec->operationTime, &tempRec->isFlag);
				/*printf("%lf %lf %d %d %d %d %d %s %d\n", tempRec->amountOfMoney, tempRec->balance,
					tempRec->year, tempRec->month, tempRec->day, tempRec->yearMonthDay, tempRec->hourMinSec,
					tempRec->operationTime, tempRec->isFlag);
				printf("*******************\n");
				system("pause");*/
				////�����зָ�
				//if (ch == '\n') {
				//	free(tempRec);
				//	break;
				//}
				temp->bankCards[i]->L->tail->next = tempRec;
				//��ȡ����Ϣ������洢�õ��������һ�����ĵ�ַ���������ӽ��
				temp->bankCards[i]->L->tail = tempRec;
				tempRec->next = NULL;
			}
			//��i=3ʱ���Ѷ�ȡ�������п���Ϣ��ÿ���������������п�
			if (i == 3) {
				i++;
				break;
			}
		}
		//��ʼ��ʣ�����п�״̬��ʶ��
		if (i < 4) {
			int j;
			for (j = i; i < 4; i++) {
				temp->bankCards[j] = (BankCard)malloc(sizeof(BankCardNode));
				temp->bankCards[j]->isFlag = 0;
			}
		}
		//���������Ϣ����
		last->next = temp;
		//��lastָ�����һ�������Ϣ���
		last = temp;
		L->tail = last;
		temp->next = NULL;
		//�ж��Ƿ����
		readCount++;
		if (readCount == L->count) {
			break;
		}
	}

	fclose(fpIdList);
	fclose(fpBankList);
	fclose(fpRecordList);
}

//�����ļ�
void SaveFile(IdcardList L) {
	FILE* fpIdList;		//����ͻ������Ϣ
	FILE* fpBankList;	//����ͻ����п���Ϣ
	FILE* fpRecordList;	//����ͻ��Ĵ�ȡ���¼
	//����Ԥ���� 
	if ((fpIdList = fopen("IdCards.txt", "w")) == NULL) {
		printf("IdCards file open error!\n");
		exit(0);
	}
	if ((fpBankList = fopen("BankCards.txt", "w")) == NULL) {
		printf("BankCards file open error!\n");
		exit(0);
	}
	if ((fpRecordList = fopen("Records.txt", "w")) == NULL) {
		printf("Records file open error!\n");
		exit(0);
	}
	int i;
	RecordList recL;
	//����ͻ�������
	fprintf(fpIdList, "%d\n", L->count);
	L = L->next;
	while (L != NULL) {
		//����ͻ������Ϣ
		fprintf(fpIdList, "%s %s %s %s %s %s %d\n", L->name, L->sex, L->nationality, 
			L->idCard, L->mobileTelephone, L->contactAddress, L->isFlag);
		//����ͻ���Ӧ�����п���Ϣ
		//����ͻ���Ӧ���п��Ĵ�ȡ���¼
		for (i = 0; i < L->isFlag; i++) {
			//����ͻ���Ӧ�����п���Ϣ
			fprintf(fpBankList, "%s %s %f %d\n", L->bankCards[i]->bankCard, 
				L->bankCards[i]->passward, L->bankCards[i]->nowBalance, L->bankCards[i]->isFlag);
			//����ͻ���Ӧ���п��Ĵ�ȡ���¼
			recL = L->bankCards[i]->L;
			//�ͻ����п���ȡ���¼����ı�ͷ�洢�Ÿÿ�����ʱ������
			fprintf(fpRecordList, "%f %s %d %d\n", recL->balance, recL->operationTime, recL->isFlag, recL->count);
			recL = recL->next;
			while (recL != NULL) {
				fprintf(fpRecordList, "%f %f %d %d %d %d %d %s %d\n", recL->amountOfMoney, recL->balance,
					recL->year, recL->month, recL->day, recL->yearMonthDay, recL->hourMinSec, recL->operationTime, recL->isFlag);
				recL = recL->next;
			}
			//ÿ���û�������������п�����isFlagΪ5ʱ����ʾ���û������ע��
			if (i == 3) {
				break;
			}
		}
		L = L->next;
		/*printf("****************\n");
		system("pause");*/
	}
	//system("pause");

	fclose(fpIdList);
	fclose(fpBankList);
	fclose(fpRecordList);
}