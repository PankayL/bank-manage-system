#ifndef _BANKCARD_H_
#define _BANKCARD_H_

#include "record.h"
#include "idcard.h"


typedef struct BankCards {
	//���п���
	char bankCard[20];
	//���п�����
	char passward[8];
	//��ǰ���
	double nowBalance;
	//��ȡ����Ϣ
	RecordList L;
	//��ʶ��
	//��Ϊ0ʱδ������Ϊ1ʱ���Ѱ�����Ϊ2ʱ��ע��
	int isFlag;
}BankCardNode, * BankCard;

typedef struct IdCard {
	//�ͻ�������
	int count;
	//�ͻ�����
	char name[10];
	//�ͻ��Ա�
	char sex[6];
	//�ͻ�����
	char nationality[6];
	//�ͻ����֤��
	char idCard[20];
	//�ͻ��ƶ��绰
	char mobileTelephone[12];
	//�ͻ���ϵ��ַ
	char contactAddress[29];
	//һ�����֤�������������п�
	BankCard bankCards[4];
	//�����Ϣ��ʶ��
	//0-4��ʾ�ۼƵ����п�����,5��ʾ���ע��
	int isFlag;
	//ָ����һ���ͻ�
	struct INode* next;
	//�洢���һ�����ĵ�ַ
	struct INode* tail;
}INode, * IdcardList;

void RequestBankCard(IdcardList L);
void GenerateBankCard(IdcardList L, int class, int belong);
void CancelBankCard(BankCard bc);
void RecoverBankCard(BankCard bc);
void PrintBankcard(IdcardList L);
void Logout(IdcardList L);
double Transfer(IdcardList IdL, RecordList ReL);
int ChangePassward(BankCard myAccount);
BankCard FindAccount(IdcardList L);

#endif // !_BANKCARD_H_
