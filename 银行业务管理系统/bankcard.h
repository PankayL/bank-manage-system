#ifndef _BANKCARD_H_
#define _BANKCARD_H_

#include "record.h"
#include "idcard.h"


typedef struct BankCards {
	//银行卡号
	char bankCard[20];
	//银行卡密码
	char passward[8];
	//当前余额
	double nowBalance;
	//存取款信息
	RecordList L;
	//标识符
	//当为0时未办理，当为1时，已办理，当为2时已注销
	int isFlag;
}BankCardNode, * BankCard;

typedef struct IdCard {
	//客户总数量
	int count;
	//客户姓名
	char name[10];
	//客户性别
	char sex[6];
	//客户国籍
	char nationality[6];
	//客户身份证号
	char idCard[20];
	//客户移动电话
	char mobileTelephone[12];
	//客户联系地址
	char contactAddress[29];
	//一个身份证最多办理四张银行卡
	BankCard bankCards[4];
	//身份信息标识符
	//0-4表示累计的银行卡数量,5表示身份注销
	int isFlag;
	//指向下一个客户
	struct INode* next;
	//存储最后一个结点的地址
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
