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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> mp;

        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }

        int preIndex = 0;

        return build(preorder, 0, inorder.size() - 1, preIndex, mp);
    }

    TreeNode* build(vector<int>& preorder, int left, int right,
                    int& preIndex, unordered_map<int, int>& mp) {
        if (left > right)
            return nullptr;

        int rootValue = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootValue);

        int mid = mp[rootValue];

        root->left = build(preorder, left, mid - 1, preIndex, mp);
        root->right = build(preorder, mid + 1, right, preIndex, mp);

        return root;
    }
};
