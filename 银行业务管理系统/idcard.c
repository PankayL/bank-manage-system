#include "idcard.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"
#pragma warning(disable : 4996)

//��ʼ�������Ϣ������
IdcardList InitIdCard(IdcardList L) {
	//�����½����Ϊͷ�ڵ㣬��ͷָ��Lָ��ͷ�ڵ�
	L = (IdcardList)malloc(sizeof(INode));
	//�Խṹ���е���������г�ʼ������
	if (!L) {
		system("cls");
		printf("�����Ϣ�������ʼ��ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//ͷ����ָ�����ÿ�
		L->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		L->tail = L;
		//�ͻ�������
		L->count = 0;
	}
	return L;
}

//��������Ϣ
void AddIdCard(IdcardList L) {
	int i;
	//�����½�� 
	IdcardList temp = (IdcardList)malloc(sizeof(INode));
	INode* middleTemp;
	IdcardList myIdTest;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� �� �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                ������");
	fflush(stdin);
	gets(temp->name);
	if (strcmp(temp->name, "\0") == 0) {
		gets(temp->name);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                 �Ա�");
	fflush(stdin);
	gets(temp->sex);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                 ������");
	fflush(stdin);
	gets(temp->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               ���֤��");
	fflush(stdin);
	gets(temp->idCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               �ֻ��ţ�");
	fflush(stdin);
	gets(temp->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               ��ס�أ�");
	fflush(stdin);
	gets(temp->contactAddress);
	//�������������֤���Ƿ��Ѿ�����
	myIdTest = L->next;
	while (myIdTest != NULL) {
		if (strcmp(myIdTest->idCard, temp->idCard) == 0) {
			system("cls");
			printf("������Ѱ����ҵ��\n");
			system("pause");
			return;
		}
		myIdTest = myIdTest->next;
	}
	/*�Խ���������ָ������и�ֵ*/
	if (!temp) {
		system("cls");
		printf("�����Ϣ�������½�����ʧ�ܣ�\n");
		system("pause");
		exit(1);
	}
	else {
		//��ʼ�����п�״̬��ʶ��
		for (i = 0; i < 4; i++) {
			temp->bankCards[i] = (BankCard)malloc(sizeof(BankCardNode));
			temp->bankCards[i]->isFlag = 0;
		}
		//���ӽ�� 
		middleTemp = L->tail;
		middleTemp->next = temp;
		//β����ָ�����ÿ�
		temp->next = NULL;
		//tail��¼������β���ĵ�ַ���������ӽ��
		L->tail = temp;
	}
	//��ʼ���ͻ���Ϣ��ʶ��,-1��ʾ���ע����0-4��ʾ�Ѱ������п�����
	temp->isFlag = 0;
	//�ͷ������½��ʱ����Ĺ��̽��������Ŀռ�
	//free(middleTemp);
	//�ͻ���������1
	L->count++;
	printf("\t\t\t\t   ��ӳɹ���\n");
	system("pause");
}

//ɾ��������ȡ����Ϣ
//�����߼���ɾ����������Ϣ�����������Ծɴ��ڣ�����ʱֻ�й���Ա��Ȩ�޲�ѯ
void deleteINode(INode* N) {
	N->isFlag = -1;
}


//ɾ��ȫ����ȡ���¼
//�����߼���ɾ����������Ϣ�����������Ծɴ��ڣ�����ʱֻ�й���Ա��Ȩ�޲�ѯ
void deleteIdcardList(IdcardList L) {
	L->isFlag = -1;
}

//�������п���������������Ϣ
void PrintIdCard(IdcardList L) {
	char bc[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                 �� �� �� �� �� ��                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          ���п��ţ�");
	gets(bc);
	if (strcmp(bc, "\0") == 0) {
		gets(bc);
	}
	L = findOwner(L, bc);
	if (L == NULL) {
		return;
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                 �� �� �� Ϣ �� ��                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               ������%-10s                    *\n", L->name);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               �Ա�%s                            *\n", L->sex);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               ������%-10s                    *\n", L->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           ���֤�ţ�%-18s            *\n", L->idCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �ֻ��ţ�%-11s                   *\n", L->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             ��ס�أ�%-29s *\n", L->contactAddress);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           ����״̬��%-10s                    *\n", L->isFlag == 5 ? "ע��" : "��ͨ");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//��Ϣ�޸�
void ChangeInfo(IdcardList L) {
	char IdCard[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*            ���֤��");
	gets(IdCard);
	if (strcmp(IdCard, "\0") == 0) {
		gets(IdCard);
	}
	L = L->next;
	while (L != NULL && strcmp(IdCard, L->idCard) != 0) {
		L = L->next;
	}
	if (L == NULL) {
		system("cls");
		printf("������Ϣ��\n");
		system("pause");
		return;
	}
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1.����              2.��ַ            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3.����              4.�ֻ���          *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             5.���п�����                          *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		char ch;
		ch = getch();
		switch (ch) {
		case'1':
			ChangeName(L);
			continue;
		case'2':
			ChangeAddress(L);
			continue;
		case'3':
			ChangeNationality(L);
			continue;
		case'4':
			ChangenMobileTelephone(L);
			continue;
		case'5':
			ChangePassward(FindAccount(L));
			continue;
		case'\r':
			break;
		default:
			continue;
		}
		break;
	}

}

//�޸�����
void ChangeName(IdcardList L) {
	system("cls");
	char name[10];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             ��������%-10s                    *\n", L->name);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             ��������");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	strcpy(L->name, name);
	system("cls");
	printf("�޸ĳɹ���\n");
	system("pause");
}

//�޸ĵ�ַ
void ChangeAddress(IdcardList L) {
	system("cls");
	char address[29];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �ɵ�ַ��%-29s *\n", L->contactAddress);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �µ�ַ��");
	gets(address);
	if (strcmp(address, "\0") == 0) {
		gets(address);
	}
	strcpy(L->contactAddress, address);
	system("cls");
	printf("�޸ĳɹ���\n");
	system("pause");
}

//�޸Ĺ���
void ChangeNationality(IdcardList L) {
	system("cls");
	char nationality[6];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �ɹ�����%-10s                    *\n", L->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             �¹�����");
	gets(nationality);
	if (strcmp(nationality, "\0") == 0) {
		gets(nationality);
	}
	strcpy(L->nationality, nationality);
	system("cls");
	printf("�޸ĳɹ���\n");
	system("pause");
}

//�޸��ֻ���
void ChangenMobileTelephone(IdcardList L) {
	system("cls");
	char mobileTelephone[12];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    �� Ϣ �� ��                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           ���ֻ��ţ�%-13s                 *\n", L->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           ���ֻ��ţ�");
	gets(mobileTelephone);
	if (strcmp(mobileTelephone, "\0") == 0) {
		gets(mobileTelephone);
	}
	strcpy(L->mobileTelephone, mobileTelephone);
	system("cls");
	printf("�޸ĳɹ���\n");
	system("pause");
}