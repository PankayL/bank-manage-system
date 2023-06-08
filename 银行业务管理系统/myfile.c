#include "myfile.h"
#include <stdlib.h>
#include <stdio.h>
#include "record.h"
#include "bankcard.h"
#include "idcard.h"
#pragma warning(disable : 4996)

//读取文件
void ReadFile(IdcardList L) {
	FILE* fpIdList;		//读取客户身份信息
	FILE* fpBankList;	//读取客户银行卡信息
	FILE* fpRecordList;	//读取客户的存取款记录
	//错误预处理 
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
	//指向身份信息链表的最后一个结点，便于存储
	IdcardList last = L;
	int count;
	fscanf(fpIdList, "%d", &L->count);
	int readCount = 0;
	int i;
	while (feof(fpIdList) == 0) {
		IdcardList temp = (IdcardList)malloc(sizeof(INode));
		//读取客户身份信息
		fscanf(fpIdList, "%s %s %s %s %s %s %d", &temp->name, &temp->sex, &temp->nationality, 
			&temp->idCard, &temp->mobileTelephone, &temp->contactAddress, &temp->isFlag);
		//读取该客户的银行卡信息
		for (i = 0; i < temp->isFlag; i++) {
			//读取客户相应的银行卡信息
			BankCard myBank = (BankCard)malloc(sizeof(BankCardNode));
			fscanf(fpBankList, "%s %s %lf %d", &myBank->bankCard, &myBank->passward, &myBank->nowBalance, &myBank->isFlag);
			temp->bankCards[i] = myBank;
			//读取每张银行卡的存取款记录
			//读取每张银行卡存取款单链表的头结点信息
			RecordList recTemp = (RecordList)malloc(sizeof(RNode));
			fscanf(fpRecordList, "%lf %s %d %d", &recTemp->balance, &recTemp->operationTime, &recTemp->isFlag, &recTemp->count);
			/*printf("%f %s %d %d\n", recTemp->balance, recTemp->operationTime, recTemp->isFlag, recTemp->count);
			printf("*****************");
			system("pause");*/
			temp->bankCards[i]->L = recTemp;
			temp->bankCards[i]->L->tail = recTemp;
			temp->bankCards[i]->L->tail->next = NULL;
			//读取每张银行卡的存取款信息
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
				////检测空行分隔
				//if (ch == '\n') {
				//	free(tempRec);
				//	break;
				//}
				temp->bankCards[i]->L->tail->next = tempRec;
				//存取款信息单链表存储该单链表最后一个结点的地址，便于增加结点
				temp->bankCards[i]->L->tail = tempRec;
				tempRec->next = NULL;
			}
			//当i=3时，已读取四张银行卡信息，每个身份最多四张银行卡
			if (i == 3) {
				i++;
				break;
			}
		}
		//初始化剩余银行卡状态标识符
		if (i < 4) {
			int j;
			for (j = i; i < 4; i++) {
				temp->bankCards[j] = (BankCard)malloc(sizeof(BankCardNode));
				temp->bankCards[j]->isFlag = 0;
			}
		}
		//连接身份信息链表
		last->next = temp;
		//让last指向最后一个身份信息结点
		last = temp;
		L->tail = last;
		temp->next = NULL;
		//判断是否读完
		readCount++;
		if (readCount == L->count) {
			break;
		}
	}

	fclose(fpIdList);
	fclose(fpBankList);
	fclose(fpRecordList);
}

//保存文件
void SaveFile(IdcardList L) {
	FILE* fpIdList;		//保存客户身份信息
	FILE* fpBankList;	//保存客户银行卡信息
	FILE* fpRecordList;	//保存客户的存取款记录
	//错误预处理 
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
	//保存客户总数量
	fprintf(fpIdList, "%d\n", L->count);
	L = L->next;
	while (L != NULL) {
		//保存客户身份信息
		fprintf(fpIdList, "%s %s %s %s %s %s %d\n", L->name, L->sex, L->nationality, 
			L->idCard, L->mobileTelephone, L->contactAddress, L->isFlag);
		//保存客户相应的银行卡信息
		//保存客户相应银行卡的存取款记录
		for (i = 0; i < L->isFlag; i++) {
			//保存客户相应的银行卡信息
			fprintf(fpBankList, "%s %s %f %d\n", L->bankCards[i]->bankCard, 
				L->bankCards[i]->passward, L->bankCards[i]->nowBalance, L->bankCards[i]->isFlag);
			//保存客户相应银行卡的存取款记录
			recL = L->bankCards[i]->L;
			//客户银行卡存取款记录链表的表头存储着该卡开卡时间和余额
			fprintf(fpRecordList, "%f %s %d %d\n", recL->balance, recL->operationTime, recL->isFlag, recL->count);
			recL = recL->next;
			while (recL != NULL) {
				fprintf(fpRecordList, "%f %f %d %d %d %d %d %s %d\n", recL->amountOfMoney, recL->balance,
					recL->year, recL->month, recL->day, recL->yearMonthDay, recL->hourMinSec, recL->operationTime, recL->isFlag);
				recL = recL->next;
			}
			//每个用户最多有四张银行卡，当isFlag为5时，表示该用户身份已注销
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