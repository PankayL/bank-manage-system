#include "search.h"
#include "bankcard.h"
#include "idcard.h"
#include <string.h>
#include <stdio.h>

//�ҵ��洢���֤��Ϣ��ַ
IdcardList findIdCard(IdcardList L) {
	system("cls");
	fflush(stdin);
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                  �� �� �� �� ֤ ��                *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*            ���֤�ţ�");
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
				printf("�������Ϣ�Ѱ����������п��������ٰ���\n");
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
	printf("�޴������Ϣ��\n");
	system("pause");
	return NULL;
}

//�ͻ���¼�����˺�����ƥ��
BankCard findMyAccount(IdcardList L, char account[], char passward[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//ƥ���˺�
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0 && strcmp(passward, L->bankCards[i]->passward) == 0) {
				if (L->bankCards[i]->isFlag == 1) {
					return (L->bankCards[i]);
				}
				system("cls");
				printf("���˺���ע����\n");
				system("pause");
				return NULL;
			}
		}
		L = L->next;
	}
	system("cls");
	printf("�˺Ż��������\n");
	system("pause");
	return NULL;
}

//�ҵ����п���ַ�����Ҵ�ȡ���¼
BankCard findInforAccount(IdcardList L, char account[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//ƥ���˺�
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0) {
				return (L->bankCards[i]);
			}
		}
		L = L->next;
	}
	system("cls");
	printf("�˺Ŵ���\n");
	system("pause");
	return NULL;
}

//�������п����ҵ�����
IdcardList findOwner(IdcardList L, char account[]) {
	int i;
	L = L->next;
	while (L != NULL) {
		//ƥ���˺�
		for (i = 0; i < L->isFlag; i++) {
			if (strcmp(account, L->bankCards[i]->bankCard) == 0) {
				return L;
			}
		}
		L = L->next;
	}
	system("cls");
	printf("���޴��˺ţ�\n");
	system("pause");
	return NULL;
}

//�����������ڲ��Ҵ�ȡ���¼
void SearchByNameDate(IdcardList L) {
	char name[10];
	int year;
	int month;
	int day;
	int i;
	RecordList recList;
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t               ��ʾ��������Ϊ0��ʾ���޶�\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                �� �� �� �� �� �� ¼               *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*              ������");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                �꣺");
	scanf_s("%d", &year);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                �£�");
	scanf_s("%d", &month);
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                �գ�");
	scanf_s("%d", &day);
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                     �� �� �� ��                   *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	//����������������ղ��Ҽ�¼
	L = L->next;
	while (L != NULL) {
		//ƥ������
		if (strcmp(L->name, name) == 0) {
			printf("\t\t\t\t* ������%-10s ���֤��%-20s     *\n", L->name, L->idCard);
			printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			printf("\t\t\t\t*        ʱ��               ���         ����       *\n");
			printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			for (i = 0; i < L->isFlag; i++) {
				printf("\t\t\t\t* ���ţ�%s                         *\n", L->bankCards[i]->bankCard);
				printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
				recList = L->bankCards[i]->L;
				//ƥ�����
				if (year > 0) {
					recList = recList->next;
					while (recList != NULL) {
						//�жϵ�ǰ��������Ƿ����������ݣ����ڣ��������ѯ��ת����һ�����п�
						if (recList->year > year) {
							printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
							break;
						}
						//�жϵ�ǰ��������Ƿ����������ݣ�
						//�����ڼ���ƥ���·ݣ�����ת����һ�����
						if (recList->year == year) {
							//����������·ݽ����жϣ�����Ϊ0���������ǰ��ݵ����м�¼
							if (month > 0) {
								//�жϵ�ǰ�����·��Ƿ���������·ݣ����ڣ��������ѯ��ת����һ�����п�
								if (recList->month > month) {
									printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
									break;
								}
								//�жϵ�ǰ�����·��Ƿ���������·ݣ�
								//�����ڼ���ƥ���գ�����ת����һ�����
								if (recList->month == month) {
									//����������ս����жϣ����������Ϊ0���������ǰ�·ݵļ�¼
									if (day > 0) {
										//�жϵ�ǰ�������Ƿ���������գ����ڣ��������ѯ��ת����һ�����п�
										if (recList->day > day) {
											printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
											break;
										}
										//�����������յ��ڸýڵ���������������¼
										if (recList->day == day) {
											printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
										}
									}//�����ǰ�·ݵĴ�ȡ���¼
									else {
										printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
									}
								}
							}//�����ǰ��ݵ����м�¼
							else {
								printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
							}
						}
						recList = recList->next;
					}
					printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
					//�������˺��µļ�¼��ѯ
					continue;
				}//���Ϊ0����ʾ������м�¼
				else {
					recList = recList->next;
					while (recList != NULL) {
						printf("\t\t\t\t* %s\t%-12.3f   %-12.3f *\n", recList->operationTime, recList->amountOfMoney, recList->balance);
						recList = recList->next;
					}
					printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
				}
				//ÿ���������������п�
				if (i == 3) {
					break;
				}
			}
		}
		L = L->next;
	}
	system("pause");
}

//ģ����ѯ
//ͨ�����뻧������Ƭ�β�ѯ������Ϣ
void FuzzySearch(IdcardList L) {
	char name[10];
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                    ģ �� �� ѯ                    *\n");
	printf("\t\t\t\t*                                                   *\n");
	printf("\t\t\t\t*                ������");
	gets(name);
	if (strcmp(name, "\0") == 0) {
		gets(name);
	}
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*   %-10s                                      *\n", name);
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*                    �� �� �� ��                    *\n");
	printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t\t\t*  ����         ���֤                ���п�        *\n");
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

//KMPƥ���ַ�Ƭ��
// ������ҳɹ�����λ��
// �������ʧ�ܷ���-1
//��һ������Ϊԭ�ַ������ڶ���Ϊ�����ַ����ַ���
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
		return i - modellen;   // ƥ��ɹ� �����Ӵ�λ��
	}
	else {
		return -1;
	}
}

//KMP�㷨���ú���
void getNextArr(char modelStr[], int* next)
{
	// ��ʼ��next�����һλΪ-1
	int i = 0;
	int j = -1;
	next[0] = -1;
	//int mLen = sizeof(modelStr) / sizeof(modelStr[0]);
	int mLen = strlen(modelStr);

	while (i < mLen - 1) {
		// �����ǰ׺=����׺�Ĺ���
		if (j == -1 || modelStr[i] == modelStr[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else {
			// ��û��ƥ���� ����л��� ���ݵ�λ��Ϊnext�����ָ�����һ��ƥ����
			j = next[j];
		}
	}
}


