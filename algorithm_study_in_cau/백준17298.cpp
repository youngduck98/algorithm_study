#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> record(n,0);
    vector<int> answer(n,0);
    stack<int> s;
    
    for(auto& k: record){
        cin >> k;
    }
    
    for(int i=n-1;i>=0;i--){
        while(!s.empty()&&s.top() <= record[i]){s.pop();}
        if(s.empty()){answer[i] = -1;}
        else if(s.top() > record[i]){answer[i] = s.top();}
        s.push(record[i]);
    }
    
    for(auto k: answer){
        cout << k <<" ";
    }
    
    cout << endl;
    
    return 0;
}
