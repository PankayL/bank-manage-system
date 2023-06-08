#include "record.h"
#include "bankcard.h"
#include <time.h>
#include "idcard.h"
#include <stdio.h>
#include "search.h"
#pragma warning(disable : 4996)

//申请银行卡
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
		printf("\t\t\t\t*                选 择 银 行 卡 等 级               *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    1. 普通卡                      *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    2. 金卡                        *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    3. 白金卡                      *\n");
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
	printf("\t\t\t\t*             输 入 银 行 卡 归 属 地               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  代码：");
	scanf("%d", &belong);
	eat = getchar();
	//生成银行卡号
	GenerateBankCard(L, class, belong);
	//设置密码
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  密码：");
	gets(L->bankCards[L->isFlag]->passward);
	//初始化单链表
	L->bankCards[L->isFlag]->L = InitRecordList(L->bankCards[L->isFlag]->L);
	//初始化标识符
	L->bankCards[L->isFlag]->isFlag = 1;
	//余额
	L->bankCards[L->isFlag]->nowBalance = 0;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*              银 行 卡 申 请 成 功                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           卡号：");
	printf("%s               *\n", L->bankCards[L->isFlag]->bankCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	//银行卡数量
	L->isFlag++;
	system("pause");
}

//生成银行卡号
void GenerateBankCard(IdcardList L, int class, int belong) {
	long long i;
	int num = 0;
	int personal = 0;
	char bc[20];
	while (1) {
		//获取中间的九位私人码
		for (i = 10; i <= 18; i++) {
			srand(time(0) + i * (i % (i + 1)));
			personal = (int)(personal * 10 + rand() % (9 - 0 + 1));
		}
		sprintf(L->bankCards[L->isFlag]->bankCard, "%d%d%d", class, belong, personal);
		//计算出最后一位的校验码的值
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
		//查看生成的新账号是否已经被申请
		int i;
		IdcardList myId;
		myId = L->next;
		while (myId != NULL) {
			//匹配账号
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

//注销银行卡
void CancelBankCard(BankCard bc) {
	bc->isFlag = 2;
}

//恢复银行卡
void RecoverBankCard(BankCard bc) {
	bc->isFlag = 1;
}

//根据身份证信息输出银行卡号
void PrintBankcard(IdcardList L) {
	int i;
	char idCard[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                请 输 入 身 份 信 息               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t              身份证号：");
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
	//L == NULL，即走到最后，并没有匹配到相应的身份信息
	if (L == NULL) {
		system("cls");
		printf("查无此信息！\n");
		system("pause");
		return;
	}
	//匹配到身份信息，输出该身份下的银行卡信息
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*                              银 行 卡 如 下                             *\n");
	if (L->isFlag == 5) {
		printf("\t\t\t* 身份已注销                                                               *\n");
	}
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*       银行卡号         状态        开户时间           最后执行时间      *\n");
	printf("\t\t\t*                                                                         *\n");
	for (i = 0; i < L->isFlag; i++) {
		printf("\t\t\t*  %s   %s   %s  %s  *\n", L->bankCards[i]->bankCard, L->bankCards[i]->isFlag == 1 ? "开通" : "注销",
			L->bankCards[i]->L->operationTime, L->bankCards[i]->L->tail->operationTime);
		if (i == 3) {
			break;
		}
	}
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//注销银行卡
void Logout(IdcardList L) {
	char account[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                   注 销 银 行 卡                  *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             银行卡号：");
	gets(account);
	if (strcmp(account, "\0") == 0) {
		gets(account);
	}
	BankCard bc = findInforAccount(L, account);
	if (bc->isFlag == 2) {
		system("cls");
		printf("该账号已注销！\n");
		system("pause");
		return;
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                     是 否 注 销                   *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          1.是                     0.否            *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	char ch;
	ch = getch();
	switch (ch) {
	case'1':
		bc->isFlag = 2;
		system("cls");
		printf("注销成功！\n");
		system("pause");
		break;
	default:
		system("cls");
		printf("取消成功！\n");
		system("pause");
	}
}

//修改密码
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
	printf("\t\t\t\t*          旧密码：");
	for (i = 0; (oldPass[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	oldPass[i] = '\0';
	printf("\n\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          新密码：");
	for (i = 0; (newPass[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	newPass[i] = '\0';
	printf("\n\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*        确认密码：");
	for (i = 0; (makeSure[i] = getch()) != '\r'; i++) {
		printf("*");
	}
	makeSure[i] = '\0';
	if (strcmp(oldPass, myAccount->passward) != 0) {
		system("cls");
		printf("旧密码错误！\n");
		system("pause");
		return 0;
	}
	if (strcmp(newPass, makeSure) == 0) {
		strcpy(myAccount->passward, newPass);
		system("cls");
		printf("密码修改成功！\n");
		system("pause");
		return 1;
	}
	else {
		system("cls");
		printf("两次密码输入不一致\n");
		system("pause");
		return 0;
	}
}

//匹配银行卡号
BankCard FindAccount(IdcardList L) {
	int i;
	char account[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          银行卡号：");
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
	printf("查无信息！\n");
	system("pause");
	return NULL;
}