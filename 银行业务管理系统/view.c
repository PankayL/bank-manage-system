#include "view.h"
#include "idcard.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "myfile.h"
#include "mysort.h"

//主菜单页面
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
		printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   1. 管理员页面                   *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   2. 客户页面                     *\n");
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

//管理员页面
void ManageView(IdcardList L) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1. 添加客户     2.办理新卡            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3. 信息查询     4.信息排序            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             5. 银行卡注销                         *\n");
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

//管理员密码
void ManagePass(IdcardList L) {
	char* p;
	int i;
	p = "123456";
	char ch[10] = "";
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                  密码：");
	for (i = 0; (ch[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	ch[i] = '\0';
	if (strcmp(ch, p) == 0) {
		ManageView(L);
	}
	else {
		system("cls");
		printf("密码错误！\n");
		system("pause");
	}
}

//客户页面
void CustomerView(IdcardList L, BankCard myAccount) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*   余额：");
		printf("%-12.3f                              *\n", myAccount->nowBalance);
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1.存钱            2.取钱              *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3.转账            4.修改密码          *\n");
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
				printf("登录失效，请重新登录！\n");
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

//客户登录
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
	printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               账号：");
	fflush(stdin);
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               密码：");
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

//信息查询页面
void InforSearchView(IdcardList L) {
	char ch = '*';
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       1.存取款记录              2.银行卡信息      *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       3.身份信息                4.姓名日期查记录  *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*       5.模糊查询                6.信息修改        *\n");
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

//输出特定客户的存取款信息
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
	printf("\t\t\t\t*           欢 迎 使 用 银 行 存 取 系 统           *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          银行卡号：");
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
	printf("\t\t\t\t*                   存 取 款 记 录                  *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          时 间          金额          余额        *\n");
	printf("\t\t\t\t*                                                   *\n");
	if (printRecordList(bc->L) == 0) {
		system("pause");
		return;
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//信息排序界面
void InforSort(IdcardList L) {
	char ch;
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                     信 息 排 序                   *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   1. 姓名排序                     *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                   2. 操作时间排序                 *\n");
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