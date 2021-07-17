#include <iostream>
#include <chrono>
#include <future>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
using namespace std;

struct TASK {
	TASK() {}
	TASK(double occurredTime_, double requiredCycle_, double constraintTime_, unsigned int RSUseg_, unsigned int TaskID_)
		:occurredTime(occurredTime_), requiredCycle(requiredCycle_), constraintTime(constraintTime_), RSUseg(RSUseg_), TaskID(TaskID_) {}
	double occurredTime;
	double requiredCycle;
	double constraintTime;
	unsigned int RSUseg;
	unsigned int TaskID;
	bool operator < (const TASK &other) {
		return occurredTime < other.occurredTime;
	}
};
vector<TASK> Tasks;

constexpr unsigned int RSUNum = 5, SRVNum = 9, TaskNum = 50, Local = 0, lineNum = 3, carGenerateGap = 2;
constexpr double propagationDelay[RSUNum][SRVNum] = {
	{0, 0.004, 0.004, 0.006, 0.009, 0.010, 0.011, 0.012, 0.011},
	{0, 0.005, 0.004, 0.004, 0.007, 0.008, 0.009, 0.010, 0.009},
	{0, 0.006, 0.005, 0.003, 0.006, 0.007, 0.008, 0.009, 0.008},
	{0, 0.009, 0.008, 0.006, 0.003, 0.004, 0.005, 0.006, 0.005},
	{0, 0.012, 0.011, 0.009, 0.006, 0.007, 0.008, 0.003, 0.002}
};
constexpr double serverResource[SRVNum] = { 0, 4.0, 5.0, 7.0, 5.0, 4.0, 7.0, 5.0, 4.0 };

double taskCache[TaskNum][SRVNum];
stack<double> stk[SRVNum];	//has 종료시간
int selected[TaskNum];	//Run 내부변수로 선언.
unsigned int globalOptimal , currentValue;


//Testing
long long int chk;
chrono::system_clock::time_point start;
//Testing

void generateData()
{
	Tasks.resize(TaskNum);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> uniformOccurredTime(0, 3);
	uniform_real_distribution<double> uniformRequiredCycle(0.6, 0.8);
	uniform_real_distribution<double> uniformConstraint(0.115, 0.16);
	//uniform_real_distribution<double> uniformConstraint(0.130, 0.160);
	//uniform_real_distribution<double> uniformConstraint(0.160, 0.230);

	for (int i = 0; i < TaskNum; ++i) {

		TASK task;

		task.occurredTime = uniformOccurredTime(gen) + i/lineNum * carGenerateGap;
		task.requiredCycle = uniformRequiredCycle(gen);
		task.constraintTime = uniformConstraint(gen);

		
		double Car_x = 33.33 * (task.occurredTime - i / lineNum * carGenerateGap); //33.33m/s -> 120km/h
		
		task.RSUseg = Car_x / 20;

		Tasks[i] = task;
	}

	
	sort(Tasks.begin(), Tasks.end());
	for (int i = 0; i < TaskNum; ++i)
		Tasks[i].TaskID = i;
}

void makeCache()
{
	for (int i = 0; i < TaskNum; ++i) 
		for (int j = 1; j < SRVNum; ++j)
			taskCache[i][j] = Tasks[i].requiredCycle / serverResource[j];
}

void RunDFS(int carIdx )
{
	++chk;
	if (carIdx == TaskNum)	//TaskNUM
	{
		int subOptimal = 0;

		for (int i = 0; i < TaskNum; ++i)
			if (selected[i] != Local)
				++subOptimal;

		if (globalOptimal < subOptimal) {
			globalOptimal = subOptimal;
			for (int i = 0; i < TaskNum; ++i)
				cout << selected[i] << " ";
			cout << " value : " << subOptimal <<'\n';
		}

		if (chk % 1000000000 == 0) {
			cout << chk << '\n';
			for (int i = 0; i < TaskNum; ++i)
				cout << selected[i] << " ";
			cout << " value : " << subOptimal << '\n';
			chrono::duration<double> dur = std::chrono::system_clock::now() - start;
			cout << dur.count() << "(s)" << '\n';
		}
		return;
	}

	for (int srv = 0; srv < SRVNum; ++srv) {

		if (srv != 0 && taskCache[carIdx][srv] + propagationDelay[Tasks[carIdx].RSUseg][srv] > Tasks[carIdx].constraintTime ) 
			continue;
		
		if (srv != 0 && (!stk[srv].empty() && stk[srv].top() > Tasks[carIdx].occurredTime))
			continue;

		if (currentValue + (TaskNum - carIdx) <= globalOptimal)
			continue;

		selected[carIdx] = srv;
		if (srv != 0) {
			stk[srv].push(Tasks[carIdx].occurredTime + taskCache[carIdx][srv] + propagationDelay[Tasks[carIdx].RSUseg][srv]);
			++currentValue;
		}

		RunDFS(carIdx + 1);

		selected[carIdx] = 0;
		if (srv != 0) {
			stk[srv].pop();
			--currentValue;
		}
	}
}

int main()
{
	start = chrono::system_clock::now();

	generateData();
	makeCache();
	
	fill(selected, selected + TaskNum, -1);
	RunDFS(0);
	
	chrono::duration<double> dur = std::chrono::system_clock::now() - start;

	cout <<"Finished time"<< dur.count() << "(s)" << '\n';
	cout << globalOptimal << '\n';
	cout << chk;
	int a;
	cin >> a;
	return 0;
}

