#ifndef _IDCARD_H_
#define _IDCARD_H_

#include "bankcard.h"

typedef struct IdCard* IdcardList;
typedef struct IdCard INode;

IdcardList InitIdCard(IdcardList L);
void AddIdCard(IdcardList L);
void deleteINode(INode* N);
void deleteIdcardList(IdcardList L);
void PrintIdCard(IdcardList L);
void ChangeInfo(IdcardList L);
void ChangeName(IdcardList L);
void ChangeAddress(IdcardList L);
void ChangeNationality(IdcardList L);
void ChangenMobileTelephone(IdcardList L);

#endif // !_IDCARD_H_
