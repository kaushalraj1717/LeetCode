/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findDepthLeft(TreeNode* root){
        if (root == NULL) return 0;
        return 1 + findDepthLeft(root->left);
    }


    int countNodes(TreeNode* root) {
        if (root == NULL) return 0;
        int depth_L = findDepthLeft(root->left);
        int depth_R = findDepthLeft(root->right);

        // Either left tree is full (largest in row continues to left)
        // Or right tree is full (full row, largest ended in next row on left)
        // Counting each level gives us: 1 + 2 + 4 ... + 2^(depth_R - 1)
        // = 2^depth_R - 1. Since we also need to include this node, it is 2^depth_R
        int counted = pow(2, depth_R);

        if (depth_L == depth_R){
            // 1 + count(depth_L == depth_R) + rest
            return counted + countNodes(root->right);
    
        } else{
            // 1 + count(depth_R) + rest
            return counted + countNodes(root->left);
        }
        
    }
};