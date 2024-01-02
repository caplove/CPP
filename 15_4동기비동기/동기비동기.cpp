
// ����-�񵿱�
// promise, future, async,pacakge_task, shared_future, condition_variable
// ����� �� �۾��� ������, ���� �۾��� ������ �� �ִ�.(������, line by line)
// �񵿱�� �� �۾��� ������ �ʾƵ�, ���� �۾��� ������ �� �ִ�.(������, parallel) -> ��Ƽ������

// promise-future �ǹ� ( producer-consumer ����� ����������, �� ����ؼ� ��ȣ)
//���� � ������ T �� ����ؼ�, �񵿱������� ���� �޾Ƴ��ڴ� ��� �ǹ̴�, 
// �̷��� (future) ������ T �� ���ϴ� �����͸� ���� �ְڴ� ��� ��� (promise) ��� �� �� �ֽ��ϴ�.

// promise, future ����(����)
// promise<int> p; // ������ ������ Ÿ�� ����
// future<int> data = pr.get_future();
// p->set_value(***) : ����� �����ϴ� ���. �ش� ����� data(future) �� ����.
// data.wait() : �̷��� ��ӵ� �����͸� ���� �� ���� ��ٸ���.
// data.get() : ���� �����͸� �����Ѵ�.


// future_status �� ready, timeout, deferred ������ ���¸� ���� �� �ִ�.
// ready : promise �� future �� ������.
// timeout : ���� �غ� �ȵ�
// deferred : promise �� future �� �������� ����.

// multiple thread���� promise, future ����Ϸ���, shared_future �� ����ؾ� �Ѵ�.
// shared_future �� ���� �����忡�� ���ÿ� ����� �� �ִ�.


//�ռ� promise �� packaged_task �� �񵿱������� ������ �ϱ� ���ؼ���, �����带 ��������� �����ؼ� �����ؾ߸� �߽��ϴ�. 
// ������ std::async �� � �Լ��� �����Ѵٸ�, �ƿ� �����带 �˾Ƽ� ���� �ش� �Լ��� �񵿱������� �����ϰ�, 
// �� ������� future �� �����մϴ�.




#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

void worker(std::promise<string>* p) {
	// ����� �����ϴ� ���. �ش� ����� future �� ����.
	p->set_value("some data");
}
void main1() {
	std::promise<string> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���.
	std::future<string> data = p.get_future();

	std::thread t(worker, &p); // promise �� worker �� �Ѱ��ش�.

	// �̷��� ��ӵ� �����͸� ���� �� ���� ��ٸ���.
	data.wait();

	// wait �� �����ߴٴ� ���� future �� �����Ͱ� �غ�Ǿ��ٴ� �ǹ�.
	// ����� wait ���� �׳� get �ص� wait �� �Ͱ� ����.
	std::cout << "���� ������ : " << data.get() << std::endl;

	t.join();
}


// promise, future ���� ó��
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

void worker2(std::promise<string>* p) {
	try {
		throw std::runtime_error("Some Error!");
	}
	catch (...) {
		// set_exception ���� exception_ptr �� �����ؾ� �Ѵ�.
		p->set_exception(std::current_exception());
	}
}
void main2() {
	std::promise<string> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���.
	std::future<string> data = p.get_future();

	std::thread t(worker2, &p);

	// �̷��� ��ӵ� �����͸� ���� �� ���� ��ٸ���.
	data.wait();

	try {
		data.get();
	}
	catch (const std::exception& e) {
		std::cout << "���� : " << e.what() << std::endl;
	}
	t.join();
}



// promise, future timeout, wait_for
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>

void worker3(std::promise<void>* p) {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	p->set_value();
}
void main3() {
	// void �� ��� ��� ��ü�� �������� ������, future �� set �� �Ǿ���
	// �ȵǾ������� ������ ��ġ �÷����� ������ ������ �� �ֽ��ϴ�.
	std::promise<void> p;

	// �̷��� string �����͸� ���� �ְڴٴ� ���.
	std::future<void> data = p.get_future();

	std::thread t(worker3, &p);

	// �̷��� ��ӵ� �����͸� ���� �� ���� ��ٸ���.
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// ���� �غ� �ȵ�
		if (status == std::future_status::timeout) {
			std::cerr << ">";
		}
		// promise �� future �� ������.
		else if (status == std::future_status::ready) {
			std::cout << "�����Ͱ� �غ�Ǿ����ϴ�." << std::endl;
			break;
		}
	}
	t.join();
}



// multiple thread���� promise, future ����Ϸ���, shared_future �� ����ؾ� �Ѵ�.
// shared_future �� ���� �����忡�� ���ÿ� ����� �� �ִ�.
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using std::thread;

void runner(std::shared_future<void> start) {
	start.get();
	std::cout << "���!" << std::endl;
}

void main4() {
	std::promise<void> p;
	std::shared_future<void> start = p.get_future();

	thread t1(runner, start);
	thread t2(runner, start);
	thread t3(runner, start);
	thread t4(runner, start);

	// ����� cerr �� std::cout ���� �ٸ��� ���۸� ������� �ʱ� ������ �͹̳ο�
	// �ٷ� ��µȴ�.
	std::cerr << "�غ�...";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << "��!" << std::endl;

	p.set_value();

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

// packaged_task�� �񵿱������� �����ϱ�
// packaged_task �� promise �� future �� ������ ���̴�.
// packaged_task �� �Լ��� �����ؼ�, future �� �����ϴ� �Լ��� ����� �ش�.
//  data.get(), promise p; p.set_value() �� ������� �ʾƵ� �ȴ�.
#include <future>
#include <iostream>
#include <thread>

int some_task(int x) { return 10/x; }

void main5() {
	// int(int) : int �� �����ϰ� ���ڷ� int �� �޴� �Լ�. (std::function ����)
	std::packaged_task<int(int)> task(some_task);

	std::future<int> start = task.get_future();

	//std::thread t(std::move(task), 5);
	std::thread t(std::move(task), 2);

	// �����̸� ����� ���, ���ܰ� �߻��ϸ� ���� ���
	try {
		std::cout << "��� : " << start.get() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "���� : " << e.what() << std::endl;
	}
	t.join();
}



// std::async �� �񵿱������� �����ϱ�
// �ռ� promise �� packaged_task �� �񵿱������� ������ �ϱ� ���ؼ���, �����带 ��������� �����ؼ� �����ؾ߸� �߽��ϴ�.
// ������ std::async �� � �Լ��� �����Ѵٸ�, �ƿ� �����带 �˾Ƽ� ���� �ش� �Լ��� �񵿱������� �����ϰ�,
// �� ������� future �� �����մϴ�.

// std::async �� std::launch::async, std::launch::deferred �ΰ��� ������� ������ �� �ִ�.
// std::launch::async : ���ο� �����带 ���� �񵿱������� �����Ѵ�.
// std::launch::deferred : �Լ��� ȣ���ϴ� ������ �����Ѵ�. (lazy evaluation)
// std::launch::async | std::launch::deferred : ���߿� �ϳ��� �����Ѵ�. (default)
// std::launch::async �� std::thread �� �����ϰ� �����带 ���� �ٷ� �����Ѵ�.
// std::launch::deferred �� std::thread �� �ٷ� ����� ������� �ʰ�, �Լ��� ȣ���ϴ� ������ �����Ѵ�.


#include <future>
#include <iostream>
#include <thread>
#include <vector>

// std::accumulate �� ����
int sum(const std::vector<int>& v, int start, int end) {
	int total = 0;
	for (int i = start; i < end; ++i) {
		total += v[i];
	}
	return total;
}

int parallel_sum(const std::vector<int>& v) {
	// lower_half_future �� 1 ~ 500 ���� �񵿱������� ����
	// ����� ���� �Լ��� ����ϸ� �� �� ����ϰ� ǥ���� �� �� �ִ�.
	// --> std::async([&v]() { return sum(v, 0, v.size() / 2); });
	std::future<int> lower_half_future =
		std::async(std::launch::async, sum, cref(v), 0, v.size() / 2); // cref : const reference

	// upper_half �� 501 ���� 1000 ���� ����
	int upper_half = sum(v, v.size() / 2, v.size());

	return lower_half_future.get() + upper_half;
}

void main6() {
	std::vector<int> v;
	v.reserve(1000);

	for (int i = 0; i < 1000; ++i) {
		v.push_back(i + 1);
	}

	std::cout << "1 ���� 1000 ������ �� : " << parallel_sum(v) << std::endl;
}





#include <future>
#include <iostream>
#include <thread>

int do_work(int x) {
	// x �� ������ ���� ���� �Ѵ�.
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return x;
}

void do_work_parallel() {
	auto f1 = std::async([]() { do_work(3); });
	auto f2 = std::async([]() { do_work(3); });
	do_work(3);

	f1.get();
	f2.get();
}

void do_work_sequential() {
	do_work(3);
	do_work(3);
	do_work(3);
}

#include <chrono>

void main7() {
	std::cout << "parallel" << std::endl;
	// ó���ð� ����, ���
	auto start = std::chrono::high_resolution_clock::now();
	do_work_parallel();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s\n";

	std::cout << "sequential" << std::endl;
	// ó���ð� ����, ���
	start = std::chrono::high_resolution_clock::now();
	do_work_sequential();
	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s\n";
}




void main() {
	main1();
	main2();
	main3();
	main4();
	main5();
	main6();
	main7();
}


