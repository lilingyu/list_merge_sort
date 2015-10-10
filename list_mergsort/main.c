//
//  main.c
//  list_mergsort
//
//  Created by LiLingyu on 15/10/10.
//  Copyright © 2015年 LiLingyu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void printlist(node* head)
{
    while (NULL != head) {
        printf("%d\t", head->data);
        head = head->next;
    }
    printf("\n");
}

void deletelist(node* head)
{
    int len = 0;
    while (NULL != head) {
        len++;
        node* tmp = head;
        head = head->next;
        
        free(tmp);
    }
}
node* merge(node* np1, node* np2)
{
    //combine 2 list
    node* head = (node*)malloc(sizeof(*head));
    node* originhead = head;
    while (NULL!=np1 && NULL!=np2) {
        if (np1->data<np2->data) {
            head->next = np1;
            head = head->next;
            np1 = np1->next;
        }
        else
        {
            head->next = np2;
            head = head->next;
            np2 = np2->next;
        }
    }
    
    if (NULL != np1) {
        head->next = np1;
    }
    
    if (NULL != np2) {
        head->next = np2;
    }
    
    head = originhead->next;
    free(originhead);
    
    return head;
}

void list_mergesort(node** headp)
{
    node* head = *headp;
    //1. part into 2 lists
    if (NULL == head) {
        return;
    }
    if (NULL == head->next)
    {
        return;
    }
    
    node* slow = head;
    node* slowpre = slow;
    node* fast = head;
    while (NULL != fast) {
        slowpre = slow;
        slow = slow->next;
        fast = fast->next;
        if (NULL != fast) {
            fast = fast->next;
        }
        else
        {
            break;
        }
    }
    
    slowpre->next = NULL;
    list_mergesort(&head);
    list_mergesort(&slow);
    
    *headp = merge(head, slow);
}



int main(int argc, const char * argv[]) {
    const int LEN = 8;
    
    int a[LEN];
    
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i<LEN; i++) {
        a[i] = rand()%LEN;
    }
    for (int i = 0; i<LEN; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    
    node* head = (node*)malloc(sizeof(*head));
    head->next = NULL;
    //form a list
    node* cur = head;
    for (int i = 0; i<LEN; i++) {
        node* tmp = (node*)malloc(sizeof(*tmp));
        tmp->data = a[i];
        tmp->next = NULL;
        
        cur->next = tmp;
        
        cur = cur->next;
    }
    printlist(head->next);
    
    list_mergesort(&(head->next));
    
    printlist(head->next);
    
    deletelist(head);
    
    return 0;
}
