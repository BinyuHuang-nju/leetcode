#include <iostream>
using namespace std;
#include <vector>
#include <map>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Solution1��
C++��hash+dfs
ִ����ʱ�� 8 ms , ������ C++ �ύ�л����� 74.92% ���û�
�ڴ����ģ� 13.1 MB , ������ C++ �ύ�л����� 100.00% ���û�

ʹ��hash�����н��洢target�����Ƚڵ��target�ڵ����Ϣ��
location�����ж�targetλ��ĳ�ڵ�ĺδ���0����target���Ǹýڵ㣬
1����targetλ�ڸýڵ���������2����targetλ�ڸýڵ���������
depth���ڼ�¼ĳ�ڵ���target֮��ľ��룬ע�⣬�ýڵ�һ����target��target���Ƚڵ㡣
���㷽����computeDpeth������
��hash����ÿ���ڵ����dfs��
���ýڵ����target������dfs���洢�����Լ�����ΪK���ӽڵ㣻
���ýڵ���target�����Ƚڵ㣬ͨ��depth��ø����Ƚڵ���target�ľ��룬��Ϊdis��
��
��dis>K�����ؿ��ǣ���Ϊ�ýڵ��ýڵ���һ�����ڵ���target���������K��
��dis==K���򽫸����Ƚڵ�洢���ɣ�
��dis<K����ʱͨ��location������Ƚڵ�q������һ��û��target��������
���õ��ýڵ�Ϊq����һ���ӽڵ㣬����ΪK-dis-1������dfs��
(dis�Ǹ����Ƚڵ㵽target�ľ��룬1�Ǹ����Ƚڵ㵽��һ���ӽڵ�ľ���)
*/
class Solution1 {

private:
    map<TreeNode*, int> location; // -1:not child,0:me,1:left child,2:right child
    map<TreeNode*, int> depth;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root)
            return {};
        computeDepth(root, target);
        vector<int> results;
        for (map<TreeNode*, int>::iterator iter = location.begin(); iter != location.end(); iter++) {
            if (iter->second == 0) {
                increaseNode(results, iter->first, K);
            }
            else if (iter->second == 1) {
                int dis = INT_MAX;
                if (depth.count(iter->first))
                    dis = depth[iter->first];
                if (dis < K) {
                    increaseNode(results, iter->first->right, K - dis - 1);
                }
                else if (dis == K)
                    results.push_back(iter->first->val);
            }
            else if (iter->second == 2) {
                int dis = INT_MAX;
                if (depth.count(iter->first))
                    dis = depth[iter->first];
                if (dis < K)
                    increaseNode(results, iter->first->left, K - dis - 1);
                else if (dis == K)
                    results.push_back(iter->first->val);
            }
        }
        return results;
    }
private:
    void increaseNode(vector<int>& results, TreeNode* root, int distance) {
        if (!root)
            return;
        if (distance == 0)
            results.push_back(root->val);
        else {
            if (root->left)
                increaseNode(results, root->left, distance - 1);
            if (root->right)
                increaseNode(results, root->right, distance - 1);
        }
    }
    int computeDepth(TreeNode* root, TreeNode* target) {
        if (root == target) {
            location[root] = 0;
            depth[root] = 0;
            return 0;
        }
        if (!root->left && !root->right) {
            //location[root] = -1;
            return -1;
        }
        int num1 = -2, num2 = -2;
        if (root->left) {
            num1 = computeDepth(root->left, target);
        }
        if (root->right) {
            num2 = computeDepth(root->right, target);
        }
        if (num1 >= 0) {
            location[root] = 1;
            depth[root] = num1 + 1;
            return (num1 + 1);
        }
        if (num2 >= 0) {
            location[root] = 2;
            depth[root] = num2 + 1;
            return (num2 + 1);
        }
        return -1;
    }
};


/* Solution2:
C++ hash+dfs
ִ����ʱ��4 ms, ������ C++ �ύ�л�����94.27%���û�
�ڴ����ģ�9.9 MB, ������ C++ �ύ�л�����100.00%���û�
����Solution1��˼�룬��location��¼ĳ�ڵ��Ƿ�Ϊtarget�����Ƚڵ㣬���ǣ�
target���������������������л����䱾��
���ｫ��Щlocation�м�¼�����Ƚڵ���б任��ʹtarget��Ϊ�任������ĸ��ڵ㡣
�����ڽ���(changeChild)ǰ�ȵ���һ��increaseNode��֮���ٵ���һ�Σ�ԭ�����ڣ�
�������£�target�����������ǿ��ӽڵ㣬�ټ��ϱ任���丸�ڵ�Ҳ��Ϊ��
�����ӽڵ㣬��ôtarget���������ӽڵ㣬�ڲ��ı����ݽṹ������£��ڵ��޷�
��ţ��������ֱ���ȼ���target�������о���targetΪK�Ľڵ㣬����target������ȫ��������
��target�������丸�ڵ���Ϊ�����µ��ӽڵ㡣����ٵ���increaseNode�㲻�����
��ֵ��ע����ǣ���KΪ0����������£���target�ᱻд�����Σ�������Ȱ�K=0
���������
*/
class Solution2 {

private:
    map<TreeNode*, int> location; // -1:not child,0:me,1:left child,2:right child
    //map<TreeNode*, TreeNode*> child;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root)
            return {};
        if (K == 0)
            return { target->val };
        isAncestry(root, target);
        vector<int> results;
        increaseNode(results, target, K);
        changeChild(root, NULL);
        increaseNode(results, target, K);
        return results;
    }
private:

    void changeChild(TreeNode* root,TreeNode* parent) {
        if (!root)
            return;
        if (!location.count(root) || location[root] < 0)
            return;
        if (location[root] == 0) {
            root->right = NULL;
            root->left = parent;
        }
        else if (location[root] == 1) {
            changeChild(root->left, root);
            root->left = parent;
        }
        else if (location[root] == 2) {
            changeChild(root->right, root);
            root->right = parent;
        }
    }
    void increaseNode(vector<int>& results, TreeNode* root, int distance) {
        if (!root)
            return;
        if (distance == 0)
            results.push_back(root->val);
        else {
            if (root->left)
                increaseNode(results, root->left, distance - 1);
            if (root->right)
                increaseNode(results, root->right, distance - 1);
        }
    }
    bool isAncestry(TreeNode* root, TreeNode* target) {
        if (root == target) {
            location[root] = 0;
            return true;
        }
        if (!root->left && !root->right) {
            //location[root] = -1;
            return false;
        }
        bool haveTarget1 = false, haveTarget2 = false;
        if (root->left) {
            haveTarget1 = isAncestry(root->left, target);
        }
        if (root->right) {
            haveTarget2 = isAncestry(root->right, target);
        }
        if (haveTarget1) {
            location[root] = 1;
            return true;
        }
        if (haveTarget2) {
            location[root] = 2;
            return true;
        }
        return false;
    }
};