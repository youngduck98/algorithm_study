#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class my_que {
public:
	vector<string> list;
	int max_size;
	int time;
private:
	int front;
	int rear;
public:
	my_que(int size);
	int inque(string k);
	string pop();
	void push(string k);
	void print();
};

my_que::my_que(int size) {
	this->max_size = size;
	this->list = vector<string>(max_size + 1, "\0");
	this->front = max_size;
	this->rear = max_size;
	this->time = 0;
}

//캐시의 최대 크기가 30밖에 되지 않아 별도의 자료구조를 만들지 않고 list를 돌아서 찾는다.
//unordered_map등을 활용할 수도 있다.
int my_que::inque(string k) {
	for (int i = (this->front + 1) % (max_size + 1); (this->rear + 1) % (max_size + 1) != i; i = (i + 1) % (max_size + 1)) {
		if (this->list[i] == k) {
			return i;
		}
	}
	return -1;
}

string my_que::pop() {
	if (this->front == this->rear)
		return "\0";
	string a = this->list[this->rear];
	this->rear = (this->rear + max_size) % (this->max_size + 1);
	return a;
}

void my_que::print() {
	for (int i = (this->front + 1) % (max_size + 1); (this->rear + 1) % (max_size + 1) != i; i = (i + 1) % (max_size + 1)) {
		cout << list[i] << " ";
	}
	cout << endl;
}

void my_que::push(string k) {
	int in = this->inque(k);//못 찾으면 -1, 찾으면 해당 index return;
	int t = 0;
	//안에 있음.
	if (in != -1) {
		//해당 원소 erase
		list.erase(list.begin() + in);

		//지울 당시 front가 rear의 앞에 있다면  
		if (this->front < this->rear) {
			//앞쪽에 null문자만 추가해 주고 범위 조절 후 종료.
			list.insert(list.begin(), "\0");
			this->front++;
		}
		//그렇지 않다면
		else {
			list.insert(list.begin() + this->rear + 1, "\0");
			if (in <= this->rear) {
				this->rear = (this->rear + max_size) % (max_size + 1);
			}
			else {
				this->front++;
			}
		}
		t -= 4;
	}
	//안에 없고 꽉 찼음
	else if (this->rear == (this->front + max_size) % (max_size + 1)) {this->pop();}

	//공통push
	this->list[this->front] = k;
	this->front = (this->front + max_size) % (max_size + 1);
	t += 5;
	time += t;
}

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	my_que mq(cacheSize);

	for (string s : cities) {
		//대소문자 구분을 하지 않으므로
		transform(s.begin(), s.end(), s.begin(), ::toupper);
		mq.push(s);
	}

	answer = mq.time;
	return answer;
}

int main() {
	vector<string> cities = { "Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome" };
	int cachesize = 3;
	cout << solution(cachesize, cities) << endl;
}