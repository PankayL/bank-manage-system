#include "view.h"
#include "idcard.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "myfile.h"
#include "mysort.h"

//���˵�ҳ��
void MainView() {
	IdcardList L = NULL;
	L = InitIdCard(L);
	ReadFile(L);
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   1. ����Աҳ��                   *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   2. �ͻ�ҳ��                     *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			ManagePass(L);
			continue;
		case'2':
			CustomerPass(L);
			continue;
		case'\r':
			SaveFile(L);
			system("cls");
			break;
		default:
			continue;
		}
		break;
	}
}

//����Աҳ��
void ManageView(IdcardList L) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1. ��ӿͻ�     2.�����¿�            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3. ��Ϣ��ѯ     4.��Ϣ����            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             5. ���п�ע��                         *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			AddIdCard(L);
			continue;
		case'2':
			RequestBankCard(L);
			continue;
		case'3':
			InforSearchView(L);
			continue;
		case'4':
			InforSort(L);
			continue;
		case'5':
			Logout(L);
			continue;
		case'\r':
			break;
		default:
			continue;
		}
		break;
	}
}

//����Ա����
void ManagePass(IdcardList L) {
	char* p;
	int i;
	p = "123456";
	char ch[10] = "";
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                  ���룺");
	for (i = 0; (ch[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	ch[i] = '\0';
	if (strcmp(ch, p) == 0) {
		ManageView(L);
	}
	else {
		system("cls");
		printf("�������\n");
		system("pause");
	}
}

//�ͻ�ҳ��
void CustomerView(IdcardList L, BankCard myAccount) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*   ��");
		printf("%-12.3f                              *\n", myAccount->nowBalance);
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1.��Ǯ            2.ȡǮ              *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3.ת��            4.�޸�����          *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			myAccount->nowBalance = addRNode(myAccount->L, 1);
			continue;
		case'2':
			myAccount->nowBalance = addRNode(myAccount->L, 2);
			continue;
		case'3':
			myAccount->nowBalance = Transfer(L, myAccount->L);
			continue;
		case'4':
			if (ChangePassward(myAccount) == 1) {
				system("cls");
				printf("��¼ʧЧ�������µ�¼��\n");
				system("pause");
				break;
			}
			continue;
		case'\r':
			break;
		default:
			continue;
		}
		break;
	}
}

//�ͻ���¼
void CustomerPass(IdcardList L) {
	char account[20];
	char passward[10];
	int i;
	//char eat;
	BankCard myAccount;
	system("cls");
	//eat = getchar();
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               �˺ţ�");
	fflush(stdin);
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               ���룺");
	fflush(stdin);
	for (i = 0; (passward[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	passward[i] = '\0';
	myAccount = findMyAccount(L, account, passward);
	if (myAccount != NULL) {
		CustomerView(L, myAccount);
	}
	return;
}

//��Ϣ��ѯҳ��
void InforSearchView(IdcardList L) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       1.��ȡ���¼              2.���п���Ϣ      *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       3.�����Ϣ                4.�������ڲ��¼  *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       5.ģ����ѯ                6.��Ϣ�޸�        *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			PrintRecord(L);
			continue;
		case'2':
			PrintBankcard(L);
			continue;
		case'3':
			PrintIdCard(L);
			continue;
		case'4':
			SearchByNameDate(L);
			continue;
		case'5':
			FuzzySearch(L);
			continue;
		case'6':
			ChangeInfo(L);
			continue;
		case'\r':
			break;
		default:
			continue;
		}
		break;
	}
}

//����ض��ͻ��Ĵ�ȡ����Ϣ
void PrintRecord(IdcardList L) {
	BankCard bc;
	char account[20];
	//char eat;
	system("cls");
	//eat = getchar();
	fflush(stdin);
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           �� ӭ ʹ �� �� �� �� ȡ ϵ ͳ           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          ���п��ţ�");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	bc = findInforAccount(L, account);
	if (bc == NULL) {
		return;
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                   �� ȡ �� �� ¼                  *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          ʱ ��          ���          ���        *\n");
	printf("\t\t\t\t*                                                   *\n");
	if (printRecordList(bc->L) == 0) {
		system("pause");
		return;
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//��Ϣ�������
void InforSort(IdcardList L) {
	char ch;
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                     �� Ϣ �� ��                   *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   1. ��������                     *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   2. ����ʱ������                 *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		ch = getch();
		switch (ch) {
		case'1':
			SortByName(L);
			continue;
		case'2':
			SortByTime(L);
			continue;
		case'\r':
			break;
		default:
			continue;
		}
		break;
	}
}