#ifndef _RECORD_H_
#define _RECORD_H_

typedef struct Record {
	//存取款记录金额、存取款后当前余额
	double amountOfMoney;
	double balance;
	//存取款操作年月日、时分秒
	//采用整型，用于根据操作时间的排序比较
	int year;
	int month;
	int day;
	int yearMonthDay;
	int hourMinSec;
	//存取款完整日期，方便输出
	char operationTime[30];
	//标识符,负责判断客户是否具有访问权限
	//当为1时，客户可以访问并浏览自己的存取款信息；为0时，客户无权访问
	int isFlag;
	//记录存取款结点个数
	int count;
	//指向下一条存取款记录的储存地址
	struct Record* next;
	//存储最后一个结点的地址，在进行增加存取款记录时不必从头开始查询
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

