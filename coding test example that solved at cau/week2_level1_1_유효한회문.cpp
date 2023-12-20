#include<stack>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    bool aA_check(char a, char b) {
        if (a == b) { return true; }
        else if (abs(a - b) == abs('a' - 'A')) { return true; }
        return false;
    }

    bool check(string s, int& index1, int& index2) {
        stack<int> mirror;
        bool one_chance = true;
        int mid = s.length() / 2;

        if (s.length() % 2) {//odd
            for (int i = 0; i < mid; i++) { mirror.push(s[i]); }

            for (int i = mid + 1; i < s.length(); i++) {
                if (!aA_check(mirror.top(), s[i])) { index2 = i; break; }
                mirror.pop();
            }
        }
        else {//even
            for (int i = 0; i < mid; i++) { mirror.push(s[i]); }

            for (int i = mid; i < s.length(); i++) {
                if (!aA_check(mirror.top(), s[i])) { index2 = i; break; }
                mirror.pop();
            }
        }
        index1 = mirror.size() - 1;
        if (mirror.empty()) { return true; }
        else { return false; }
    }

    bool isPalindrome(string s) {
        int index1 = -1, index2 = -1;
        string::iterator si = s.begin();
        while (si != s.end()) {
            if (*si == ':' || *si == ',' || *si == ' ') {
                s.erase(si);
                si--;
            }
            si++;
        }
        cout << s << endl;
        string s1 = s;
        string s2 = s;

        if (check(s, index1, index2)) {
            return true;
        }
        s1.erase(s1.begin() + index1);
        s2.erase(s2.begin() + index2);
        if (check(s1, index1, index2)) {
            return true;
        }
        if (check(s2, index1, index2)) {
            return true;
        }
        return false;
    }
};
