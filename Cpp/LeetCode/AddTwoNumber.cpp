/*
https://leetcode.com/problems/add-two-numbers/
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* sumList = nullptr;
        ListNode* currentSumList = nullptr;
        ListNode* currentL1 = l1;
        ListNode* currentL2 = l2;
        int lengthL1 = 0;
        int lengthL2 = 0;

        while(currentL1 != nullptr){
            lengthL1++;
            currentL1 = currentL1->next;
        }
        while(currentL2 != nullptr){
            lengthL2++;
            currentL2 = currentL2->next;
        }

        if(lengthL1>lengthL2){
            currentL1 = l1;
            currentL2 = l2;
        }else{
            currentL2 = l1;
            currentL1 = l2;
        }
        int carry = 0;
        while(currentL1 != nullptr){
            int sum = currentL1->val + carry;
            if(currentL2 != nullptr){
                sum = sum + currentL2->val;
                currentL2 = currentL2->next;
            }
            carry = sum/10;
            int remainder = sum%10;
            ListNode *newNode = new ListNode(remainder);
            if(sumList == nullptr){
                sumList = newNode;
                currentSumList = sumList;
            }else{
                currentSumList->next = newNode;
                currentSumList = currentSumList->next;
            }
            currentL1 = currentL1->next;
        }

        if(carry>0){
            ListNode *newNode = new ListNode(carry);
            currentSumList->next = newNode;
        }
        return sumList;
    }
};