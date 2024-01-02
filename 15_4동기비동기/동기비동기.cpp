
// 동기-비동기
// promise, future, async,pacakge_task, shared_future, condition_variable
// 동기는 한 작업이 끝나야, 다음 작업을 수행할 수 있다.(순차적, line by line)
// 비동기는 한 작업이 끝나지 않아도, 다음 작업을 수행할 수 있다.(병렬적, parallel) -> 멀티쓰레드

// promise-future 의미 ( producer-consumer 비슷한 역할이지만, 더 깔끔해서 선호)
//내가 어떤 쓰레드 T 를 사용해서, 비동기적으로 값을 받아내겠다 라는 의미는, 
// 미래에 (future) 쓰레드 T 가 원하는 데이터를 돌려 주겠다 라는 약속 (promise) 라고 볼 수 있습니다.

// promise, future 사용법(순서)
// promise<int> p; // 연산후 돌려줄 타입 지정
// future<int> data = pr.get_future();
// p->set_value(***) : 약속을 이행하는 모습. 해당 결과는 data(future) 에 들어간다.
// data.wait() : 미래에 약속된 데이터를 받을 때 까지 기다린다.
// data.get() : 받은 데이터를 리턴한다.


// future_status 는 ready, timeout, deferred 세가지 상태를 가질 수 있다.
// ready : promise 가 future 를 설정함.
// timeout : 아직 준비가 안됨
// deferred : promise 가 future 를 설정하지 않음.

// multiple thread에서 promise, future 사용하려면, shared_future 를 사용해야 한다.
// shared_future 는 여러 쓰레드에서 동시에 사용할 수 있다.


//앞서 promise 나 packaged_task 는 비동기적으로 실행을 하기 위해서는, 쓰레드를 명시적으로 생성해서 실행해야만 했습니다. 
// 하지만 std::async 에 어떤 함수를 전달한다면, 아예 쓰레드를 알아서 만들어서 해당 함수를 비동기적으로 실행하고, 
// 그 결과값을 future 에 전달합니다.




#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

void worker(std::promise<string>* p) {
	// 약속을 이행하는 모습. 해당 결과는 future 에 들어간다.
	p->set_value("some data");
}
void main1() {
	std::promise<string> p;

	// 미래에 string 데이터를 돌려 주겠다는 약속.
	std::future<string> data = p.get_future();

	std::thread t(worker, &p); // promise 를 worker 에 넘겨준다.

	// 미래에 약속된 데이터를 받을 때 까지 기다린다.
	data.wait();

	// wait 이 리턴했다는 뜻이 future 에 데이터가 준비되었다는 의미.
	// 참고로 wait 없이 그냥 get 해도 wait 한 것과 같다.
	std::cout << "받은 데이터 : " << data.get() << std::endl;

	t.join();
}


// promise, future 예외 처리
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
		// set_exception 에는 exception_ptr 를 전달해야 한다.
		p->set_exception(std::current_exception());
	}
}
void main2() {
	std::promise<string> p;

	// 미래에 string 데이터를 돌려 주겠다는 약속.
	std::future<string> data = p.get_future();

	std::thread t(worker2, &p);

	// 미래에 약속된 데이터를 받을 때 까지 기다린다.
	data.wait();

	try {
		data.get();
	}
	catch (const std::exception& e) {
		std::cout << "예외 : " << e.what() << std::endl;
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
	// void 의 경우 어떠한 객체도 전달하지 않지만, future 가 set 이 되었냐
	// 안되었느냐의 유무로 마치 플래그의 역할을 수행할 수 있습니다.
	std::promise<void> p;

	// 미래에 string 데이터를 돌려 주겠다는 약속.
	std::future<void> data = p.get_future();

	std::thread t(worker3, &p);

	// 미래에 약속된 데이터를 받을 때 까지 기다린다.
	while (true) {
		std::future_status status = data.wait_for(std::chrono::seconds(1));

		// 아직 준비가 안됨
		if (status == std::future_status::timeout) {
			std::cerr << ">";
		}
		// promise 가 future 를 설정함.
		else if (status == std::future_status::ready) {
			std::cout << "데이터가 준비되었습니다." << std::endl;
			break;
		}
	}
	t.join();
}



// multiple thread에서 promise, future 사용하려면, shared_future 를 사용해야 한다.
// shared_future 는 여러 쓰레드에서 동시에 사용할 수 있다.
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using std::thread;

void runner(std::shared_future<void> start) {
	start.get();
	std::cout << "출발!" << std::endl;
}

void main4() {
	std::promise<void> p;
	std::shared_future<void> start = p.get_future();

	thread t1(runner, start);
	thread t2(runner, start);
	thread t3(runner, start);
	thread t4(runner, start);

	// 참고로 cerr 는 std::cout 과는 다르게 버퍼를 사용하지 않기 때문에 터미널에
	// 바로 출력된다.
	std::cerr << "준비...";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr << "땅!" << std::endl;

	p.set_value();

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

// packaged_task로 비동기적으로 실행하기
// packaged_task 는 promise 와 future 를 결합한 것이다.
// packaged_task 는 함수를 래핑해서, future 를 리턴하는 함수로 만들어 준다.
//  data.get(), promise p; p.set_value() 를 사용하지 않아도 된다.
#include <future>
#include <iostream>
#include <thread>

int some_task(int x) { return 10/x; }

void main5() {
	// int(int) : int 를 리턴하고 인자로 int 를 받는 함수. (std::function 참조)
	std::packaged_task<int(int)> task(some_task);

	std::future<int> start = task.get_future();

	//std::thread t(std::move(task), 5);
	std::thread t(std::move(task), 2);

	// 정상이면 결과값 출력, 예외가 발생하면 예외 출력
	try {
		std::cout << "결과 : " << start.get() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "예외 : " << e.what() << std::endl;
	}
	t.join();
}



// std::async 로 비동기적으로 실행하기
// 앞서 promise 나 packaged_task 는 비동기적으로 실행을 하기 위해서는, 쓰레드를 명시적으로 생성해서 실행해야만 했습니다.
// 하지만 std::async 에 어떤 함수를 전달한다면, 아예 쓰레드를 알아서 만들어서 해당 함수를 비동기적으로 실행하고,
// 그 결과값을 future 에 전달합니다.

// std::async 는 std::launch::async, std::launch::deferred 두가지 방식으로 실행할 수 있다.
// std::launch::async : 새로운 쓰레드를 만들어서 비동기적으로 실행한다.
// std::launch::deferred : 함수를 호출하는 시점에 실행한다. (lazy evaluation)
// std::launch::async | std::launch::deferred : 둘중에 하나를 선택한다. (default)
// std::launch::async 는 std::thread 와 동일하게 쓰레드를 만들어서 바로 실행한다.
// std::launch::deferred 는 std::thread 를 바로 만들어 사용하지 않고, 함수를 호출하는 시점에 실행한다.


#include <future>
#include <iostream>
#include <thread>
#include <vector>

// std::accumulate 와 동일
int sum(const std::vector<int>& v, int start, int end) {
	int total = 0;
	for (int i = start; i < end; ++i) {
		total += v[i];
	}
	return total;
}

int parallel_sum(const std::vector<int>& v) {
	// lower_half_future 는 1 ~ 500 까지 비동기적으로 더함
	// 참고로 람다 함수를 사용하면 좀 더 깔끔하게 표현할 수 도 있다.
	// --> std::async([&v]() { return sum(v, 0, v.size() / 2); });
	std::future<int> lower_half_future =
		std::async(std::launch::async, sum, cref(v), 0, v.size() / 2); // cref : const reference

	// upper_half 는 501 부터 1000 까지 더함
	int upper_half = sum(v, v.size() / 2, v.size());

	return lower_half_future.get() + upper_half;
}

void main6() {
	std::vector<int> v;
	v.reserve(1000);

	for (int i = 0; i < 1000; ++i) {
		v.push_back(i + 1);
	}

	std::cout << "1 부터 1000 까지의 합 : " << parallel_sum(v) << std::endl;
}





#include <future>
#include <iostream>
#include <thread>

int do_work(int x) {
	// x 를 가지고 무슨 일을 한다.
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
	// 처리시간 측정, 출력
	auto start = std::chrono::high_resolution_clock::now();
	do_work_parallel();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s\n";

	std::cout << "sequential" << std::endl;
	// 처리시간 측정, 출력
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


