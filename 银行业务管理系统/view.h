#ifndef _VIEW_H_
#define _VIEW_H_

#include "idcard.h"

void MainView();
void ManageView(IdcardList L);
void ManagePass(IdcardList L);
void CustomerView(IdcardList L, BankCard myAccount);
void CustomerPass(IdcardList L);
void InforSearchView(IdcardList L);
void PrintRecord(IdcardList L);
void InforSort(IdcardList L);

#endif // !_VIEW_H_

