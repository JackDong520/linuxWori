#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <mutex>
#include "main.h"
#include "BTree.h"
#include "BPlusTree.h"
#include "Context.h"

void test() {

    /*************************************直接调用B  B+ 的调度使用****************************************/
    /************************************* Direct call B + B method ****************************************/
    BTree bt;
    BPlusTree bpt;

    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        bt.insert(arr[i]);
        bpt.insert(arr[i]);
    }
    printf("no delete data:\n");
    printf("display about B-Tree:\n");
    bt.level_display();
    bt.inorder_print();
    printf("\n\n");

    printf("display about B+ Tree:\n");
    bt.level_display();
    bt.inorder_print();
    printf("\n");
    bpt.linear_print();
    printf("\n");
    bt.NodeNum_print();
    bpt.NodeNum_print();
    printf("delete data...\n");
    int todel[] = {15, 18, 23, 30, 31, 52, 50};

    for (int i = 0; i < sizeof(todel) / sizeof(int); i++) {
        printf("after delete %d\n", todel[i]);
        bt.del(todel[i]);
        bpt.del(todel[i]);
    }

    bt.NodeNum_print();
    bpt.NodeNum_print();

    printf("\n\ndelete after data:\n");
    printf("display about B-Tree:\n");
    bt.level_display();
    bt.inorder_print();
    printf("\n\n");

    printf("display about B+ Tree:\n");
    bpt.level_display();
    bpt.inorder_print();
    printf("\n");
    bpt.linear_print();
    printf("\n");

    /***************************************************************************************************/
    /***************************************************************************************************/
    /************************************* 用策略方法的调用B    ****************************************/
    /************************************* strategy pattern method ****************************************/

    printf("strategy method start\n");

    //“具体策略类”只在定义多个“调度类”时使用
    Context *Context_A = new Context(new BTree()),
            *Context_B = new Context(new BPlusTree());

    //调用方法，只通过“调度类”实现，算法之间的差异已被屏蔽
    int arrnum[] = {10, 2, 3, 4, 5, 9, 8, 7, 6, 1};
    for (int i = 0; i < sizeof(arrnum) / sizeof(int); i++) {
        Context_A->Insert(arrnum[i]);
        Context_B->Insert(arrnum[i]);
    }
    Context_A->Inorder_Print();
    printf("\n\n");
    Context_B->LevelDisplay();

    /***************************************************************************************************/
    /***************************************************************************************************/

}

/**
 * 使用线程来查找链表中的值
 * @param PNode
 * @param shuxing
 * @param value
 */
std::mutex NodeListMutex;
std::mutex NodeListLenMutex;

int NodeLen = 0;

int main() {
    //test();


//    BPlusTree bpt;
//
//    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
//    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
//        bpt.insert(arr[i]);
//    }
//    bpt.linear_print();
//    bpt.level_display();
//    bpt.inorder_print();
//    printf("\n");

    Wdnmd fDataNode = initDataList();

    Wdnmd *NewNode = static_cast<Wdnmd *>(malloc(sizeof(Wdnmd)));

    NewNode->next = nullptr;
    for (int i = 0; i < MAXROWLINE; i++) {
        NewNode->shuxing[i] = 222;
        NewNode->zhi[i] = "2233";
    }

    putDataToList(&fDataNode, NewNode);

    Wdnmd *NewNode1 = static_cast<Wdnmd *>(malloc(sizeof(Wdnmd)));

    NewNode1->next = nullptr;
    for (int i = 0; i < MAXROWLINE; i++) {
        NewNode1->shuxing[i] = 222;
        NewNode1->zhi[i] = "2233";
    }
    putDataToList(&fDataNode, NewNode1);


    Wdnmd *NewNode2 = static_cast<Wdnmd *>(malloc(sizeof(Wdnmd)));

    NewNode2->next = nullptr;
    for (int i = 0; i < MAXROWLINE; i++) {
        NewNode2->shuxing[i] = 222;
        NewNode2->zhi[i] = "2233";
    }
    putDataToList(&fDataNode, NewNode2);


    Wdnmd *NewNode3 = static_cast<Wdnmd *>(malloc(sizeof(Wdnmd)));

    NewNode3->next = nullptr;
    for (int i = 0; i < MAXROWLINE; i++) {
        NewNode3->shuxing[i] = 222;
        NewNode3->zhi[i] = "2233";
    }
    putDataToList(&fDataNode, NewNode3);

    // outlink(&fDataNode);

    std::cout << "Hello, World!" << std::endl;

    // Wdnmd *head = createlink();
    //traversalAllNodes(&fDataNode);

//    findValue(&fDataNode, 2, "2233");
    // findRangRowValue(&fDataNode, 2, "2233", 2, 3);

    runRangeRowSearch(&fDataNode, 2, "2233", 2, 3);
    runRangeRowSearch(&fDataNode, 2, "2233", 1, 3);
    runRangeRowSearch(&fDataNode, 2, "2233", 2, 4);
    runRangeRowSearch(&fDataNode, 2, "2233", 4, 10);
    runRangeRowSearch(&fDataNode, 2, "2233", 2, 3);
    return 0;
}

/**
 * 在链表的结尾添加新的节点
 * @param spNode
 * @param NewNode
 */
void putDataToList(Wdnmd *spNode, Wdnmd *NewNode) {
    NodeListMutex.lock();
    printf("Thread Mutex Lock!\n");
    Wdnmd *pNode = spNode;

    if (pNode == nullptr) {
        printf("null dataNode");
    }
    int nodeTotal = 0;
    while (pNode->next != nullptr) {
        pNode = pNode->next;
        printf("exit node %d \n", nodeTotal++);
    }
    pNode->next = NewNode;
    modifyNodeLen(1);
    printf("total node :%d \n", nodeTotal++);
    NodeListMutex.unlock();
    printf("Thread Mutex UnLock!\n");
}

/**
 * 初始化链表的头节点
 * @return
 */
Wdnmd initDataList() {
    Wdnmd datalist = Wdnmd();
    datalist.next = nullptr;
    for (int i = 0; i < MAXROWLINE; i++) {
        datalist.shuxing[i] = 222;
        datalist.zhi[i] = "2233";
    }
    modifyNodeLen(1);
    return datalist;
}

/**
 * 遍历所有的节点
 * @param pNode
 */
void traversalAllNodes(Wdnmd *pNode) {
    NodeListMutex.lock();
    printf("Thread Mutex Lock!\n");
    if (pNode == nullptr) {
        printf("null dataNode");
    }
    while (pNode != nullptr) {
        for (int i = 0; i < MAXROWLINE; i++) {
            printf("traversal : %ld \n", pNode->shuxing[i]);
            printf("traversal : %s \n", pNode->zhi[i].c_str());
            printf("%d\n", i);
        }
        pNode = pNode->next;
    }
    NodeListMutex.unlock();
    printf("Thread Mutex UnLock!\n");

}

/**
 * 将链表写入到文件
 * @param head
 */
void outlink(Wdnmd *head) {
    Wdnmd *p = head->next;
    char buffer[1024];
    getcwd(buffer, 1024);
    printf("%s", buffer);
    FILE *w = fopen("output.txt", "w");
    if (w == nullptr) {
        printf("打开文件失败!");
        return;
    }

    while (p) {
        //输出链表节点数据到屏幕 
        printf("%ld ", p->shuxing[2]);
        //输出链表节点数据到文件output.txt 
        fprintf(w, "%ld ", p->shuxing[2]);
        p = p->next;
    }
    printf("\n");
    fprintf(w, "\n");
    fclose(w);
}

/**
 * 读取文件创建链表
 * @return
 */
Wdnmd *createlink() {
    Wdnmd *head = (Wdnmd *) malloc(sizeof(Wdnmd));
    int t;
    Wdnmd *p;
    Wdnmd *q;
    p = q = head;
    FILE *r = fopen("output.txt", "r");
    if (r == nullptr) {
        printf("打开文件失败!");
        return nullptr;
    }

    while (fscanf(r, "%d", &t) != EOF) {
        q = (Wdnmd *) malloc(sizeof(Wdnmd));
        printf("file data :%d\n", t);
        q->shuxing[1] = t;
        p->next = q;
        p = q;
    }
    p->next = nullptr;
    return head;
}


void findValue(Wdnmd *spNode, int shuxing, const string &value) {
    NodeListMutex.lock();
    printf("Thread Mutex Lock!\n");
    Wdnmd *pNode = spNode;
    int rowLine = 0;
    pthread_t tid = pthread_self();
    printf("pthread %u:run runSearch \n", tid);
    while (pNode != nullptr) {
        rowLine++;

        if (0 == value.compare(pNode->zhi[shuxing])) {
            printf("find %s in row %d \n", value.c_str(), rowLine);
        }

        pNode = pNode->next;
    }
    NodeListMutex.unlock();
    printf("Thread Mutex UnLock!\n");
}

/**
 * 在特定的行内搜索目标值
 * @param spNode
 * @param shuxing
 * @param value
 * @param lowRow
 * @param HighRow
 */

void findRangRowValue(Wdnmd *spNode, int shuxing, const string &value, int lowRow, int HighRow) {
    NodeListMutex.lock();
    printf("Thread Mutex Lock!\n");
    Wdnmd *pNode = spNode;
    int rowLine = 0;
    pthread_t tid = pthread_self();
    printf("pthread %u:run runRangeRowSearch  searchrange is %d to %d \n", tid, lowRow, HighRow);
    while (pNode != nullptr) {
        rowLine++;

        if (rowLine >= lowRow && HighRow >= rowLine) {
            if (0 == value.compare(pNode->zhi[shuxing])) {
                printf("find %s in row %d \n", value.c_str(), rowLine);
            }
        }
        pNode = pNode->next;
    }
    NodeListMutex.unlock();
    printf("Thread Mutex UnLock!\n");
}


void runSearch(Wdnmd *PNode, int shuxing, const string &value) {
//    std::thread thread([&]() {
//        findValue(PNode, shuxing, value);
//    });
    std::thread thread1(findValue, PNode, shuxing, value);

    thread1.join();
}

void runRangeRowSearch(Wdnmd *spNode, int shuxing, const string &value, int lowRow, int HighRow) {
    std::thread thread1(findRangRowValue, spNode, shuxing, value, lowRow, HighRow);

    thread1.join();
}

void modifyNodeLen(int i) {
    NodeListLenMutex.lock();
    printf("NodeListLenMutex Lock!\n");
    NodeLen = NodeLen + i;
    printf("the NodeLen is : %d\n", NodeLen);
    NodeListLenMutex.unlock();
    printf("NodeListLenMutex UnLock!\n");
}

