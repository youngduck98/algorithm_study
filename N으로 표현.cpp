#include <string>
#include <vector>
#include <set>
#include<iostream>

using namespace std;

int make_num(int N, int cnt){
    int answer = N;
    for(int i=0;i<cnt - 1;i++){
        answer = answer*10 + N;
    }
    return answer;
}

void insert_num_to_set(set<int>& dest, set<int>fs, set<int>es){
    for(auto fn: fs){
        for(auto en:es){
            if(fn != 0 && en != 0){
                dest.insert(fn+en);
                dest.insert(fn-en);
                dest.insert(fn*en);
                dest.insert(fn/en);
                dest.insert(en/fn);
            }
        }
    }
}

int solution(int N, int number) {
    vector<set<int>> dp(9);
    dp[1].insert(N);
    if(N == number){
        return 1;
    }
    for(int h=2;h<9;h++){
        dp[h].insert(make_num(N, h));
        for(int fn = 0;fn<=h/2;fn++){
            insert_num_to_set(dp[h], dp[fn], dp[h - fn]);
        }
        
        for(auto k: dp[h]){
            if(k == number){
                return h;
            }
        }
    }
    
   return -1;
}
