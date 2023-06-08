#ifndef _RECORD_H_
#define _RECORD_H_

typedef struct Record {
	//��ȡ���¼����ȡ���ǰ���
	double amountOfMoney;
	double balance;
	//��ȡ����������ա�ʱ����
	//�������ͣ����ڸ��ݲ���ʱ�������Ƚ�
	int year;
	int month;
	int day;
	int yearMonthDay;
	int hourMinSec;
	//��ȡ���������ڣ��������
	char operationTime[30];
	//��ʶ��,�����жϿͻ��Ƿ���з���Ȩ��
	//��Ϊ1ʱ���ͻ����Է��ʲ�����Լ��Ĵ�ȡ����Ϣ��Ϊ0ʱ���ͻ���Ȩ����
	int isFlag;
	//��¼��ȡ�������
	int count;
	//ָ����һ����ȡ���¼�Ĵ����ַ
	struct Record* next;
	//�洢���һ�����ĵ�ַ���ڽ������Ӵ�ȡ���¼ʱ���ش�ͷ��ʼ��ѯ
	struct Record* tail;
}RNode, * RecordList;

RecordList InitRecordList(RecordList L);
double addRNode(RecordList L, int isFlag);
void modifyRNode(RecordList L, double amountOfMoney, double balance, int yearMonthDay, int hourMinSec, char operationTime[]);
void deleteRNode(RecordList L);
void deleteRecordList(RecordList L);
int printRecordList(RecordList L);
void getTime(RecordList L);

#endif // !_RECORD_H_

