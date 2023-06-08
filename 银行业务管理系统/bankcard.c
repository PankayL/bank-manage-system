#include "record.h"
#include "bankcard.h"
#include <time.h>
#include "idcard.h"
#include <stdio.h>
#include "search.h"
#pragma warning(disable : 4996)

//�������п�
void RequestBankCard(IdcardList L) {
	L = findIdCard(L);
	if (L == NULL) {
		return;
	}
	char ch, eat;
	int class;
	int belong;
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                ѡ �� �� �� �� �� ��               *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    1. ��ͨ��                      *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    2. ��                        *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    3. �׽�                      *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			class = 622911;
			break;
		case'2':
			class = 622913;
			break;
		case'3':
			class = 622915;
			break;
		default:
			continue;
		}
		break;
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �� �� �� �� �� �� �� ��               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  ���룺");
	scanf("%d", &belong);
	eat = getchar();
	//�������п���
	GenerateBankCard(L, class, belong);
	//��������
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  ���룺");
	gets(L->bankCards[L->isFlag]->passward);
	//��ʼ��������
	L->bankCards[L->isFlag]->L = InitRecordList(L->bankCards[L->isFlag]->L);
	//��ʼ����ʶ��
	L->bankCards[L->isFlag]->isFlag = 1;
	//���
	L->bankCards[L->isFlag]->nowBalance = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*              �� �� �� �� �� �� ��                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           ���ţ�");
	printf("%s               *\n", L->bankCards[L->isFlag]->bankCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	//���п�����
	L->isFlag++;
	system("pause");
}

//�������п���
void GenerateBankCard(IdcardList L, int class, int belong) {
	long long i;
	int num = 0;
	int personal = 0;
	char bc[20];
	while (1) {
		//��ȡ�м�ľ�λ˽����
		for (i = 10; i <= 18; i++) {
			srand(time(0) + i * (i % (i + 1)));
			personal = (int)(personal * 10 + rand() % (9 - 0 + 1));
		}
		sprintf(L->bankCards[L->isFlag]->bankCard, "%d%d%d", class, belong, personal);
		//��������һλ��У�����ֵ
		for (i = 0; i < 18; i++) {
			if (i % 2 == 0) {
				num = num + (L->bankCards[L->isFlag]->bankCard[i] - 48) * 2;
			}
			else {
				num = num + L->bankCards[L->isFlag]->bankCard[i] - 48;
			}
		}
		num = num % 10;
		sprintf(bc, "%d%d%d%d", class, belong, personal, num);
		//�鿴���ɵ����˺��Ƿ��Ѿ�������
		int i;
		IdcardList myId;
		myId = L->next;
		while (myId != NULL) {
			//ƥ���˺�
			for (i = 0; i < myId->isFlag; i++) {
				if (strcmp(bc, myId->bankCards[i]->bankCard) == 0) {
					break;
				}
			}
			if (strcmp(bc, myId->bankCards[i]->bankCard) == 0) {
				break;
			}
			myId = myId->next;
		}
		if (myId == NULL) {
			break;
		}
	}
	sprintf(L->bankCards[L->isFlag]->bankCard, "%d%d%d%d", class, belong, personal, num);
}

//ע�����п�
void CancelBankCard(BankCard bc) {
	bc->isFlag = 2;
}

//�ָ����п�
void RecoverBankCard(BankCard bc) {
	bc->isFlag = 1;
}

//�������֤��Ϣ������п���
void PrintBankcard(IdcardList L) {
	int i;
	char idCard[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                �� �� �� �� �� �� Ϣ               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t              ���֤�ţ�");
	gets(idCard);
	if (strcmp(idCard, "\0") == 0) {
		gets(idCard);
	}
	L = L->next;
	while (L != NULL) {
		if (strcmp(idCard, L->idCard) == 0) {
			break;
		}
		L = L->next;
	}
	//L == NULL�����ߵ���󣬲�û��ƥ�䵽��Ӧ�������Ϣ
	if (L == NULL) {
		system("cls");
		printf("���޴���Ϣ��\n");
		system("pause");
		return;
	}
	//ƥ�䵽�����Ϣ�����������µ����п���Ϣ
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*                              �� �� �� �� ��                             *\n");
	if (L->isFlag == 5) {
		printf("\t\t\t* �����ע��                                                               *\n");
	}
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*       ���п���         ״̬        ����ʱ��           ���ִ��ʱ��      *\n");
	printf("\t\t\t*                                                                         *\n");
	for (i = 0; i < L->isFlag; i++) {
		printf("\t\t\t*  %s   %s   %s  %s  *\n", L->bankCards[i]->bankCard, L->bankCards[i]->isFlag == 1 ? "��ͨ" : "ע��",
			L->bankCards[i]->L->operationTime, L->bankCards[i]->L->tail->operationTime);
		if (i == 3) {
			break;
		}
	}
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//ע�����п�
void Logout(IdcardList L) {
	char account[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                   ע �� �� �� ��                  *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             ���п��ţ�");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	BankCard bc = findInforAccount(L, account);
	if (bc->isFlag == 2) {
		system("cls");
		printf("���˺���ע����\n");
		system("pause");
		return;
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                     �� �� ע ��                   *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          1.��                     0.��            *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	char ch;
	ch = getch();
	switch (ch) {
	case'1':
		bc->isFlag = 2;
		system("cls");
		printf("ע���ɹ���\n");
		system("pause");
		break;
	default:
		system("cls");
		printf("ȡ���ɹ���\n");
		system("pause");
	}
}

//�޸�����
int ChangePassward(BankCard myAccount) {
	if (myAccount == NULL) {
		return;
	}
	char oldPass[8];
	char newPass[8];
	char makeSure[8];
	int i;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          �����룺");
	for (i = 0; (oldPass[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	oldPass[i] = '\0';
	printf("\n\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          �����룺");
	for (i = 0; (newPass[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	newPass[i] = '\0';
	printf("\n\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*        ȷ�����룺");
	for (i = 0; (makeSure[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	makeSure[i] = '\0';
	if (strcmp(oldPass, myAccount->passward) != 0) {
		system("cls");
		printf("���������\n");
		system("pause");
		return 0;
	}
	if (strcmp(newPass, makeSure) == 0) {
		strcpy(myAccount->passward, newPass);
		system("cls");
		printf("�����޸ĳɹ���\n");
		system("pause");
		return 1;
	}
	else {
		system("cls");
		printf("�����������벻һ��\n");
		system("pause");
		return 0;
	}
}

//ƥ�����п���
BankCard FindAccount(IdcardList L) {
	int i;
	char account[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          ���п��ţ�");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	for (i = 0; i < L->isFlag; i++) {
		if (strcmp(L->bankCards[i]->bankCard, account) == 0) {
			return L->bankCards[i];
		}
		if (i == 3) {
			break;
		}
	}
	system("cls");
	printf("������Ϣ��\n");
	system("pause");
	return NULL;
}