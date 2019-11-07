//
// Created by root on 11/6/19.
//

#ifndef LINUXWORI_MAIN_H
#define LINUXWORI_MAIN_H

#endif //LINUXWORI_MAIN_H

#define MAXROWLINE 10
using namespace std;

typedef struct Wdnmd {
    int64_t shuxing[MAXROWLINE];
    string zhi[MAXROWLINE];
    struct Wdnmd *next;
} *pNode;

void traversalAllNodes(Wdnmd *pNode);

void putDataToList(Wdnmd *spNode, Wdnmd *NewNode);

Wdnmd initDataList();

void outlink(Wdnmd *head);

Wdnmd *createlink();

void findValue(Wdnmd *spNode, int shuxing, const string &value);

void findRangRowValue(Wdnmd *spNode, int shuxing, const string &value, int lowRow, int HighRow);

void runSearch(Wdnmd *PNode, int shuxing, const string &value);

void runRangeRowSearch(Wdnmd *spNode, int shuxing, const string &value, int lowRow, int HighRow);

void modifyNodeLen(int i);

