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

// ----------------------using brute force-------------------------------
class Solution {
public:
    ListNode* convertarrtoll(vector<int>& arr){
        if (arr.empty()) return nullptr; 
        ListNode* head = new ListNode(arr[0]);
        ListNode* mover = head;
        for(int i = 1; i < arr.size(); i++){
            ListNode* temp = new ListNode(arr[i]);
            mover->next = temp;
            mover = mover->next;
        }
        return head;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> arr;
        for(int i = 0; i < lists.size(); i++){
            ListNode* temp = lists[i];
            while(temp){
                arr.push_back(temp->val);
                temp = temp->next;
            }
        }
        sort(arr.begin(), arr.end());
        ListNode* head = convertarrtoll(arr);
        return head;
    }
};