#include "search.h"
#include "bankcard.h"
#include "idcard.h"
#include <string.h>
#include <stdio.h>

//找到存储身份证信息地址
IdcardList findIdCard(IdcardList L) {
	system("cls");
	fflush(stdin);
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  输 入 身 份 证 号                *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*            身份证号：");
	char idCard[20];
	gets(idCard);
	if (strcmp(idCard, "\0") == 0) {
		gets(idCard);
	}
	//IdcardList result = (IdcardList)malloc(sizeof(INode));
	L = L->next;
	while (L != NULL) {
		if (strcmp(L->idCard, idCard) == 0) {
			if (L->isFlag == 4) {
				system("cls");
				printf("该身份信息已办理四张银行卡，不能再办理！\n");
				system("pause");
				return NULL;
			}
			return L;
		}
		else {
			L = L->next;
		}
	}
	system("cls");
	printf("无此身份信息！\n");
	system("pause");
	return NULL;
}

//客户登录界面账号密码匹配
BankCard findMyAccount(IdcardList L, char account[], char passward[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//匹配账号
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0 && strcmp(passward, L->bankCards[i]->passward) == 0) {
				if (L->bankCards[i]->isFlag == 1) {
					return (L->bankCards[i]);
				}
				system("cls");
				printf("该账号已注销！\n");
				system("pause");
				return NULL;
			}
		}
		L = L->next;
	}
	system("cls");
	printf("账号或密码错误！\n");
	system("pause");
	return NULL;
}

//找到银行卡地址，查找存取款记录
BankCard findInforAccount(IdcardList L, char account[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//匹配账号
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0) {
				return (L->bankCards[i]);
			}
		}
		L = L->next;
	}
	system("cls");
	printf("账号错误！\n");
	system("pause");
	return NULL;
}

//根据银行卡号找到户主
IdcardList findOwner(IdcardList L, char account[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//匹配账号
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0) {
				return L;
			}
		}
		L = L->next;
	}
	system("cls");
	printf("查无此账号！\n");
	system("pause");
	return NULL;
}

//根据姓名日期查找存取款记录
void SearchByNameDate(IdcardList L) {
	char name[10];
	int year;
	int month;
	int day;
	int i;
	RecordList recList;
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t               提示：年月日为0表示不限定\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                姓 名 日 期 查 记 录               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*              姓名：");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                年：");
	scanf_s("%d", &year);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                月：");
	scanf_s("%d", &month);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                日：");
	scanf_s("%d", &day);
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                     结 果 如 下                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	//根据所输入的年月日查找记录
	L = L->next;
	while (L != NULL) {
		//匹配姓名
		if (strcmp(L->name, name) == 0) {
			printf("\t\t\t\t* 姓名：%-10s 身份证：%-20s     *\n", L->name, L->idCard);
			printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			printf("\t\t\t\t*        时间               金额         结余       *\n");
			printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			for (i = 0; i < L->isFlag; i++) {
				printf("\t\t\t\t* 卡号：%s                         *\n", L->bankCards[i]->bankCard);
				printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
				recList = L->bankCards[i]->L;
				//匹配年份
				if (year > 0) {
					recList = recList->next;
					while (recList != NULL) {
						//判断当前结点的年份是否大于所查年份，大于，则结束查询，转往下一张银行卡
						if (recList->year > year) {
							printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
							break;
						}
						//判断当前结点的年份是否等于所查年份，
						//若等于继续匹配月份，否则转入下一个结点
						if (recList->year == year) {
							//对所输入的月份进行判断，若是为0，则输出当前年份的所有记录
							if (month > 0) {
								//判断当前结点的月份是否大于所查月份，大于，则结束查询，转往下一张银行卡
								if (recList->month > month) {
									printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
									break;
								}
								//判断当前结点的月份是否等于所查月份，
								//若等于继续匹配日，否则转入下一个结点
								if (recList->month == month) {
									//对所输入的日进行判断，若输入的月为0，则输出当前月份的记录
									if (day > 0) {
										//判断当前结点的日是否大于所查日，大于，则结束查询，转往下一张银行卡
										if (recList->day > day) {
											printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
											break;
										}
										//如果所输入的日等于该节点的日则输出该条记录
										if (recList->day == day) {
											printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
										}
									}//输出当前月份的存取款记录
									else {
										printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
									}
								}
							}//输出当前年份的所有记录
							else {
								printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
							}
						}
						recList = recList->next;
					}
					printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
					//结束此账号下的记录查询
					continue;
				}//年份为0，表示输出所有记录
				else {
					recList = recList->next;
					while (recList != NULL) {
						printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
						recList = recList->next;
					}
					printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
				}
				//每个身份最多四张银行卡
				if (i == 3) {
					break;
				}
			}
		}
		L = L->next;
	}
	system("pause");
}

//模糊查询
//通过输入户主名字片段查询户主信息
void FuzzySearch(IdcardList L) {
	char name[10];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    模 糊 查 询                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                姓名：");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*   %-10s                                      *\n", name);
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                    结 果 如 下                    *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*  姓名         身份证                银行卡        *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	L = L->next;
	int i;
	while (L != NULL) {
		if (KMP(L->name, name) == -1) {
			L = L->next;
			continue;
		}
		for (i = 0; i < L->isFlag; i++) {
			printf("\t\t\t\t* %-8s %-20s %-20s*\n", L->name, L->idCard, L->bankCards[i]->bankCard);
		}
		if (i == 3) {
			L = L->next;
			continue;
		}
		L = L->next;
		/*if (KMP(L->name, name) != -1) {
			for (i = 0; i < L->isFlag; i++) {
				printf("\t\t\t\t* %-8s %-20s %-20s*\n", L->name, L->idCard, L->bankCards[i]->bankCard);
			}
			if (i == 3) {
				L = L->next;
				continue;
			}
		}
		L = L->next;*/
	}
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	system("pause");
}

//KMP匹配字符片段
// 如果查找成功返回位置
// 如果查找失败返回-1
//第一个参数为原字符串，第二个为样本字符或字符串
int KMP(char dstStr[], char modelStr[])
{
	int i = 0;
	int j = 0;
	/*int dstlen = sizeof(dstStr)/sizeof(dstStr[0]);
	int modellen = sizeof(modelStr)/sizeof(modelStr);*/
	int dstlen = strlen(dstStr);
	int modellen = strlen(modelStr);
	int next[255] = { 0 };

	getNextArr(modelStr, next);

	while ((i < dstlen) && (j < modellen)) {
		if (j == -1 || dstStr[i] == modelStr[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}

	if (j >= modellen) {
		return i - modellen;   // 匹配成功 返回子串位置
	}
	else {
		return -1;
	}
}

//KMP算法调用函数
void getNextArr(char modelStr[], int* next)
{
	// 初始化next数组第一位为-1
	int i = 0;
	int j = -1;
	next[0] = -1;
	//int mLen = sizeof(modelStr) / sizeof(modelStr[0]);
	int mLen = strlen(modelStr);

	while (i < mLen - 1) {
		// 求最大前缀=最大后缀的过程
		if (j == -1 || modelStr[i] == modelStr[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else {
			// 当没有匹配上 则进行回溯 回溯的位置为next数组的指向的下一个匹配项
			j = next[j];
		}
	}
}


