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

//ĳ���� �ִ� ũ�Ⱑ 30�ۿ� ���� �ʾ� ������ �ڷᱸ���� ������ �ʰ� list�� ���Ƽ� ã�´�.
//unordered_map���� Ȱ���� ���� �ִ�.
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
	int in = this->inque(k);//�� ã���� -1, ã���� �ش� index return;
	int t = 0;
	//�ȿ� ����.
	if (in != -1) {
		//�ش� ���� erase
		list.erase(list.begin() + in);

		//���� ��� front�� rear�� �տ� �ִٸ�  
		if (this->front < this->rear) {
			//���ʿ� null���ڸ� �߰��� �ְ� ���� ���� �� ����.
			list.insert(list.begin(), "\0");
			this->front++;
		}
		//�׷��� �ʴٸ�
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
	//�ȿ� ���� �� á��
	else if (this->rear == (this->front + max_size) % (max_size + 1)) {this->pop();}

	//����push
	this->list[this->front] = k;
	this->front = (this->front + max_size) % (max_size + 1);
	t += 5;
	time += t;
}

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	my_que mq(cacheSize);

	for (string s : cities) {
		//��ҹ��� ������ ���� �����Ƿ�
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