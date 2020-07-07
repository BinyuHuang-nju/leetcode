#include <iostream>
using namespace std;
#include <string>
#include <queue>

class Solution {
public: //̰�ģ�ÿ��R��Ӫ�Ĳ���Ա��ֹ��һ�����������D��Ӫ�Ĳ���Ա
    string predictPartyVictory(string senate) {
        queue<int> radiant;
        queue<int> dire;
        for (int i = 0; i < senate.length(); i++) {
            if (senate[i] == 'R')
                radiant.push(i);
            else
                dire.push(i);
        }
        while (!radiant.empty() && !dire.empty()) {
            int r = radiant.front();
            int d = dire.front();
            radiant.pop();
            dire.pop();
            if (r < d)
                radiant.push(r + senate.length());
            else
                dire.push(d + senate.length());
        }
        return (radiant.empty()) ? "Dire" : "Radiant";
    }
};
