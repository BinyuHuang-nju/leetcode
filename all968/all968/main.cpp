#include <iostream>
using namespace std;
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        if (!root)
            return 0;
        int num = 0;
        if (childState(root, num) == 1)
            return num + 1;
        return num;
    }
    int childState(TreeNode* root, int& num) {
        if (!root)
            return 0;             //������/�ѱ����
        if (!root->left && !root->right)
            return 1;             //��δ����� ϣ�������
        int l = childState(root->left, num), r = childState(root->right, num);
        if (l == 1 || r == 1) {
            num++;
            return 2;            // �����˼����
        }
        if (l == 2 || r == 2)
            return 0;
        return 1;
    }
};