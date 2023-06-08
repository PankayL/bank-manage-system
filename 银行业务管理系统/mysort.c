#include <stdio.h>
#include "mysort.h"
#include "idcard.h"
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

//按客户姓名进行排序
//冒泡排序
void SortByName(IdcardList L) {
    IdcardList IdOne;
    IdcardList IdTwo;
    IdcardList IdThree;
    //链表只有头结点，为空，不必进行排序
    if (L->next == NULL) {
        system("cls");
        printf("无客户！\n");
        system("pause");
        return;
    }
    //如果链表客户信息结点超过一个，则进行排序，否则直接进行输出
    IdcardList mid = L->next;
    if (mid->next != NULL) {
        int i;
        int count = L->count;
        int num;
        for (i = L->count-1; i >= 1; i--) {
            IdOne = L;
            IdTwo = L->next;
            IdThree = mid->next;
            for (num = 1; num < count; num++) {
                if (strcmp(IdTwo->name, IdThree->name) > 0) {
                    //结点位置交换
                    IdOne->next = IdThree;
                    IdTwo->next = IdThree->next;
                    IdThree->next = IdTwo;
                    //转向下两个结点的比较
                    IdOne = IdThree;
                    IdThree = IdTwo->next;
                }
                else {//转向下两个结点的比较
                    IdOne = IdOne->next;
                    IdTwo = IdTwo->next;
                    IdThree = IdThree->next;
                }
            }
            //每轮比较次数递减
            count--;
        }
    }
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t\t\t\t*                                                   *\n");
    printf("\t\t\t\t*                     姓 名 排 序                   *\n");
    printf("\t\t\t\t*                                                   *\n");
    printf("\t\t\t\t*   姓名           身份证              银行卡       *\n");
    printf("\t\t\t\t*                                                   *\n");
    L = L->next;
    while (L != NULL) {
        int j;
        for (j = 0; j < L->isFlag; j++) {
            printf("\t\t\t\t*  %-8s %-19s %-19s *\n", L->name, L->idCard, L->bankCards[j]->bankCard);
            printf("\t\t\t\t*                                                   *\n");
            if (j == 3) {
                break;
            }
        }
        L = L->next;
    }
    printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    system("pause");
}

//按客户的最后操作时间进行排序
//快速排序
void SortByTime(IdcardList L) {
    int count = 0;
    int i;
    MySortList head = (MySortList)malloc(sizeof(SNode));
    MySortList isTail = (MySortList)malloc(sizeof(SNode));
    head->next = NULL;
    head->previous = NULL;
    head->isFlag = -1;
    isTail = head;
    L = L->next;
    while (L != NULL) {
        for (i = 0; i < L->isFlag; i++) {
            MySortList temp = (MySortList)malloc(sizeof(SNode));
            temp->previous = isTail;
            isTail->next = temp;
            temp->next = NULL;
            strcpy(temp->name, L->name);
            strcpy(temp->Idcard, L->idCard);
            strcpy(temp->bankCard, L->bankCards[i]->bankCard);
            strcpy(temp->operationTime, L->bankCards[i]->L->tail->operationTime);
            /*printf("%s\n", temp->operationTime);
            system("pause");*/
            temp->yearMonthDay = L->bankCards[i]->L->tail->yearMonthDay;
            temp->hourMinSec = L->bankCards[i]->L->tail->hourMinSec;
            temp->isFlag = 0;
            isTail = temp;
            if (i == 3) {
                break;
            }
        }
        L = L->next;
    }
    //测试读取的信息是否正确
    /*head = head->next;
    while (head != NULL) {
        printf("\t\t\t\t*  %-8s%-19s  %-19s *\n", head->name, head->bankCard, head->operationTime);
        printf("\t\t\t\t*                                                   *\n");
        head = head->next;
    }
    printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    system("pause");*/
    //使最后一个结点为空结点
    MySortList temp = (MySortList)malloc(sizeof(SNode));
    temp->isFlag = -1;
    isTail->next = temp;
    temp->previous = isTail;
    temp->next = NULL;
    //第一个含有信息的结点
    MySortList low = head->next;
    //根据时间快速排序
    QSort(head, low, isTail);
    //isTail->next = NULL;
    head = head->next;
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t\t\t\t*                                                   *\n");
    printf("\t\t\t\t*               最 后 操 作 时 间 排 序             *\n");
    printf("\t\t\t\t*                                                   *\n");
    printf("\t\t\t\t*   姓名           银行卡          最后操作时间     *\n");
    printf("\t\t\t\t*                                                   *\n");
    while (head->next != NULL) {
        printf("\t\t\t\t*  %-8s%-19s  %-19s *\n", head->name, head->bankCard, head->operationTime);
        printf("\t\t\t\t*                                                   *\n");
        head = head->next;
    }
    printf("\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    system("pause");
}

//快速排序
void QSort(MySortList L, MySortList low, MySortList high) {
    if (low == high) {
        return;
    }
    MySortList pivotloc = Partition(L, low, high);
    if (pivotloc->previous->isFlag != -1) {
        if (pivotloc->previous->isFlag == 1) {
            low = pivotloc->previous;
        }
        else {
            low = pivotloc;
            while (1) {
                low = low->previous;
                if (low->previous->isFlag != 0) {
                    break;
                }
            }
            QSort(L, low, pivotloc->previous);
        }
    }
    if (pivotloc->next->isFlag != -1) {
        if (pivotloc->previous->isFlag == 1) {
            high = pivotloc->previous;
        }
        else {
            high = pivotloc;
            while (1) {
                high = high->next;
                //碰到枢轴或首尾空结点
                if (high->next->isFlag != 0) {
                    break;
                }
            }
            QSort(L, pivotloc->next, high);
        }
    }
}

//快速排序调用函数
MySortList Partition(MySortList L, MySortList low, MySortList high) {
    MySortList isFlag = low;
    isFlag->isFlag = 1;
    MySortList SortOne;
    MySortList SortTwo;
    MySortList SortThree;
    MySortList SortFour;
    int i = 0;
    while (low != high) {
       /* printf("%s\n%s\n", low->operationTime, high->operationTime);
        system("pause");*/
        //比较是相邻两个结点，即最后一次比较
        if (low->next == high) {
            if (strcmp(low->operationTime, high->operationTime) < 0) {
                SortOne = low->previous;
                SortTwo = high->next;
                SortOne->next = high;
                SortTwo->previous = low;
                high->previous = SortOne;
                high->next = low;
                low->previous = high;
                low->next = SortTwo;
                low = SortOne->next;
                high = SortTwo->previous;
            }
            break;
        }
        if (strcmp(low->operationTime, high->operationTime) < 0) {
            SortOne = low->previous;
            SortTwo = low->next;
            SortThree = high->previous;
            SortFour = high->next;
            SortOne->next = high;
            SortTwo->previous = high;
            SortThree->next = low;
            SortFour->previous = low;
            low->previous = SortThree;
            low->next = SortFour;
            high->previous = SortOne;
            high->next = SortTwo;
            low = SortOne->next;
            high = SortThree->next;
            i++;
        }
        if (i % 2 == 0) {
            high = high->previous;
        }
        else {
            low = low->next;
        }
    }
    return isFlag;
}
