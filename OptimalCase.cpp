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
constexpr unsigned int RSUNum = 5, SRVNum = 8, TaskNum = 20, SRV = 3;
constexpr double propagationDelay[RSUNum][SRVNum] = {
	{0.004, 0.004, 0.006, 0.009, 0.010, 0.011, 0.012, 0.011},
	{0.005, 0.004, 0.004, 0.007, 0.008, 0.009, 0.010, 0.009},
	{0.006, 0.005, 0.003, 0.006, 0.007, 0.008, 0.009, 0.008},
	{0.009, 0.008, 0.006, 0.003, 0.004, 0.005, 0.006, 0.005},
	{0.012, 0.011, 0.009, 0.006, 0.007, 0.008, 0.003, 0.002}
};
constexpr double serverResource[SRVNum] = { 4.0, 5.0, 7.0, 5.0, 4.0, 7.0, 5.0, 4.0 };
constexpr double computingResource[SRV] = { 4.0, 5.0, 7.0 };
double taskCache[TaskNum][SRV];
stack<double> stk[SRVNum];
bool selected[TaskNum];	//Run 내부변수로 선언.
unsigned int ans;


long long int chk;

void generateData()
{
	Tasks.resize(TaskNum);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> uniformOccurredTime(0, 3);
	uniform_real_distribution<double> uniformRequiredCycle(0.6, 0.8);
	uniform_real_distribution<double> uniformConstraint(0.15, 0.23);

	for (int i = 0; i < TaskNum; ++i) {

		TASK task;

		task.occurredTime = uniformOccurredTime(gen);
		task.requiredCycle = uniformRequiredCycle(gen);
		task.constraintTime = uniformConstraint(gen);

		
		double Car_x = 33.33 * task.occurredTime; //33.33m/s -> 120km/h
		
		//RSU seg [0,20) : 0, [20,40): 1...
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
		for (int j = 0; j < 3; ++j) 
			taskCache[i][j] = Tasks[i].requiredCycle / computingResource[j];
}

void RunDFS(int carIdx )
{
	if (carIdx == 12)
	{
		int candidate = 0;

		for (int i = 0; i < SRVNum; ++i)
			if (selected[i])
				candidate++;

		if (ans < candidate)
			ans = candidate;

		++chk;
		if (chk % 1000000000 == 0)
			cout << chk << '\n';
		return;
	}

	for (int srv = 0; srv < SRVNum; ++srv) {
		/*if (taskCache[carIdx][srv] + propagationDelay[Tasks[carIdx].RSUseg][srv] <= Tasks[carIdx].constraintTime) {
			selected[carIdx] = true;
			
			RunDFS(carIdx + 1);

			selected[carIdx] = false;

			//RunDFS(carIdx + 1); 이 방법은 느림.
		}*/
		selected[carIdx] = true;

		RunDFS(carIdx + 1);

		selected[carIdx] = false;
	}
}

int main()
{
	chrono::system_clock::time_point start = chrono::system_clock::now();

	generateData();
	makeCache();
	//Run();
	RunDFS(0);
	
	chrono::duration<double> dur = std::chrono::system_clock::now() - start;

	cout << dur.count() << "(s)" << '\n';
	cout << ans << '\n';
	cout << chk;
	return 0;
}

