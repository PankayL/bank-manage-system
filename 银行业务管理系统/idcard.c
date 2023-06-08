#include "idcard.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"
#pragma warning(disable : 4996)

//初始化身份信息单链表
IdcardList InitIdCard(IdcardList L) {
	//生成新结点作为头节点，用头指针L指向头节点
	L = (IdcardList)malloc(sizeof(INode));
	//对结构体中的数据域进行初始化操作
	if (!L) {
		system("cls");
		printf("身份信息单链表初始化失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//头结点的指针域置空
		L->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		L->tail = L;
		//客户总数量
		L->count = 0;
	}
	return L;
}

//添加身份信息
void AddIdCard(IdcardList L) {
	int i;
	//生成新结点 
	IdcardList temp = (IdcardList)malloc(sizeof(INode));
	INode* middleTemp;
	IdcardList myIdTest;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    添 加 客 户                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                姓名：");
	fflush(stdin);
	gets(temp->name);
	if (strcmp(temp->name, "\0") == 0) {
		gets(temp->name);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                 性别：");
	fflush(stdin);
	gets(temp->sex);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t                 国籍：");
	fflush(stdin);
	gets(temp->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               身份证：");
	fflush(stdin);
	gets(temp->idCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               手机号：");
	fflush(stdin);
	gets(temp->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t               居住地：");
	fflush(stdin);
	gets(temp->contactAddress);
	//检测所输入的身份证号是否已经开户
	myIdTest = L->next;
	while (myIdTest != NULL) {
		if (strcmp(myIdTest->idCard, temp->idCard) == 0) {
			system("cls");
			printf("该身份已办理该业务！\n");
			system("pause");
			return;
		}
		myIdTest = myIdTest->next;
	}
	/*对结点数据域和指针域进行赋值*/
	if (!temp) {
		system("cls");
		printf("身份信息单链表新结点添加失败！\n");
		system("pause");
		exit(1);
	}
	else {
		//初始化银行卡状态标识符
		for (i = 0; i < 4; i++) {
			temp->bankCards[i] = (BankCard)malloc(sizeof(BankCardNode));
			temp->bankCards[i]->isFlag = 0;
		}
		//连接结点 
		middleTemp = L->tail;
		middleTemp->next = temp;
		//尾结点的指针域置空
		temp->next = NULL;
		//tail记录单链表尾结点的地址，便于增加结点
		L->tail = temp;
	}
	//初始化客户信息标识符,-1表示身份注销，0-4表示已办理银行卡数量
	temp->isFlag = 0;
	//释放连接新结点时定义的过程结点所申请的空间
	//free(middleTemp);
	//客户总数量加1
	L->count++;
	printf("\t\t\t\t   添加成功！\n");
	system("pause");
}

//删除单条存取款信息
//仅在逻辑上删除单链表信息，在物理上仍旧存在，但此时只有管理员有权限查询
void deleteINode(INode* N) {
	N->isFlag = -1;
}


//删除全部存取款记录
//仅在逻辑上删除单链表信息，在物理上仍旧存在，但此时只有管理员有权限查询
void deleteIdcardList(IdcardList L) {
	L->isFlag = -1;
}

//根据银行卡号输出卡主身份信息
void PrintIdCard(IdcardList L) {
	char bc[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                 输 入 银 行 卡 号                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*          银行卡号：");
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
	printf("\t\t\t\t*                 卡 主 信 息 如 下                 *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               姓名：%-10s                    *\n", L->name);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               性别：%s                            *\n", L->sex);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*               国籍：%-10s                    *\n", L->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           身份证号：%-18s            *\n", L->idCard);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             手机号：%-11s                   *\n", L->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             居住地：%-29s *\n", L->contactAddress);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           户主状态：%-10s                    *\n", L->isFlag == 5 ? "注销" : "开通");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//信息修改
void ChangeInfo(IdcardList L) {
	char IdCard[20];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    信 息 修 改                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*            身份证：");
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
		printf("查无信息！\n");
		system("pause");
		return;
	}
	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*                    信 息 修 改                    *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             1.姓名              2.地址            *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             3.国籍              4.手机号          *\n");
		printf("\t\t\t\t*                                                   *\n");
		printf("\t\t\t\t*             5.银行卡密码                          *\n");
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

//修改姓名
void ChangeName(IdcardList L) {
	system("cls");
	char name[10];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    信 息 修 改                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             旧姓名：%-10s                    *\n", L->name);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             新姓名：");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	strcpy(L->name, name);
	system("cls");
	printf("修改成功！\n");
	system("pause");
}

//修改地址
void ChangeAddress(IdcardList L) {
	system("cls");
	char address[29];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    信 息 修 改                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             旧地址：%-29s *\n", L->contactAddress);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             新地址：");
	gets(address);
	if (strcmp(address, "\0") == 0) {
		gets(address);
	}
	strcpy(L->contactAddress, address);
	system("cls");
	printf("修改成功！\n");
	system("pause");
}

//修改国籍
void ChangeNationality(IdcardList L) {
	system("cls");
	char nationality[6];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    信 息 修 改                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             旧国籍：%-10s                    *\n", L->nationality);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*             新国籍：");
	gets(nationality);
	if (strcmp(nationality, "\0") == 0) {
		gets(nationality);
	}
	strcpy(L->nationality, nationality);
	system("cls");
	printf("修改成功！\n");
	system("pause");
}

//修改手机号
void ChangenMobileTelephone(IdcardList L) {
	system("cls");
	char mobileTelephone[12];
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    信 息 修 改                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           旧手机号：%-13s                 *\n", L->mobileTelephone);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*           新手机号：");
	gets(mobileTelephone);
	if (strcmp(mobileTelephone, "\0") == 0) {
		gets(mobileTelephone);
	}
	strcpy(L->mobileTelephone, mobileTelephone);
	system("cls");
	printf("修改成功！\n");
	system("pause");
}