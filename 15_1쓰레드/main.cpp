
// 쓰레드
// 병렬처리를 위해 사용되는 가장 기본적인 방법
// 쓰레드는 프로세스 내에서 실행되는 흐름의 단위
// 프로세스는 최소 하나의 쓰레드를 가지고 있으며, 쓰레드가 하나인 프로세스는 싱글 쓰레드 프로세스라고 한다.
// 쓰레드는 프로세스 내의 데이터를 공유하며, 프로세스 내의 쓰레드들은 동시에 실행될 수 있다.
// join() : 쓰레드가 끝날 때까지 기다린다.
// detach() : 쓰레드가 끝나도 기다리지 않는다.
// 쓰레드는 생성자에서 시작되며, 소멸자에서 종료된다.
// race condition : 여러 쓰레드가 동시에 접근하여 데이터를 변경할 때, 예상치 못한 결과가 발생하는 현상
// mutex : 여러 쓰레드가 동시에 접근하여 데이터를 변경할 때, 데이터의 일관성을 보장하기 위해 사용되는 동기화 기법
// lock_guard : mutex를 이용하여 데이터의 일관성을 보장하는 동기화 기법

// 함수
// thread : 쓰레드를 생성한다.
// join : 쓰레드가 끝날 때까지 기다린다.
// detach : 쓰레드가 끝나도 기다리지 않는다.
// get_id : 쓰레드의 id를 얻는다.
// this_thread::get_id : 현재 쓰레드의 id를 얻는다.
// this_thread::sleep_for : 현재 쓰레드를 잠시 멈춘다.
// this_thread::yield : 현재 쓰레드를 양보한다.
// this_thread::hardware_concurrency : 현재 시스템에서 동시에 실행 가능한 쓰레드의 개수를 얻는다.
// std::lock_guard : mutex를 이용하여 데이터의 일관성을 보장하는 동기화 기법





#include <iostream>
#include <thread>
#include <vector>

void worker(std::vector<long long>::iterator start, std::vector<long long>::iterator end, long long* result) {
    long long sum = 0;
    for (auto x = start; x != end; ++x) {
        sum += *x;
        }

    *result = sum;

    // thread id
    std::thread::id this_id = std::this_thread::get_id();
    printf("쓰레드 %p 에서 %lld 부터 %lld 까지 계산한 결과 : %lld \n", this_id, start, (end - 1), sum);
    }

void main1() {
    // 데이터 생성 : 1~1000000 vector
    const int MAX = 1000000;
    std::vector<long long> data(MAX);
    for (int i = 0; i < MAX; i++)
        data[i] = i;

    // thread를 이용한 합 구하기
    // thread 순서는 운영체제에 의해 결정되므로, partioal sum의 순서가 보장되지는 않는댜.
    const int NUM_OF_THRHEAD = 10;
    std::vector<long long> partial_sums(NUM_OF_THRHEAD);

    std::vector<std::thread> workers;
    for (int i = 0; i < NUM_OF_THRHEAD; i++) {
        workers.push_back(
            std::thread(
            worker, data.begin() + i * (MAX / NUM_OF_THRHEAD),
            data.begin() + (i + 1) * (MAX / NUM_OF_THRHEAD),
            &partial_sums[i]));
        }

    // worker thread가 끝날 때까지(join 할때까지) 기다린다.
    for (auto& worker : workers)
        worker.join();

    // worker thread가 끝난 후, 결과 출력
    long long total = 0;
    for (int i = 0; i < NUM_OF_THRHEAD; i++)
        total += partial_sums[i];

    std::cout << "Total Sum : " << total << std::endl;

    }

// race condition
// 여러 쓰레드가 동시에 접근하여 데이터를 변경할 때, 예상치 못한 결과가 발생하는 현상

void worker2(int& counter) {
    for (int i = 0; i < 100000; i++) {
        counter += 1;
        }
    }

void main2() {
    int counter = 0;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        // 레퍼런스로 전달하려면 ref 함수로 감싸야 한다 (지난 강좌 bind 함수 참조)
        workers.push_back(std::thread(worker2, std::ref(counter)));
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
    }


// mutex
// 여러 쓰레드가 동시에 접근하여 데이터를 변경할 때, 데이터의 일관성을 보장하기 위해 사용되는 동기화 기법
// thread 처리를 하려는 함수의 인자로 mutex 객체를 전달하고, m.lock과 m.unlock을 이용하여 데이터의 일관성을 보장한다.
// thread(fn, 인자1, 인자2(mutex& m))
// critical section : mutex로 보호되는 코드 영역
// 여기서는 result += 1 이 critical section 이다.

#include <mutex>
void worker3(int& result, std::mutex& m) {
    for (int i = 0; i < 100000; i++) {
        m.lock();
        result += 1;
        m.unlock();
        }
    }

void main3() {
    int counter = 0;
    std::mutex m;  // 우리의 mutex 객체

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker3, std::ref(counter), std::ref(m))); // thread (fn, 인자1, 인자2)
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
    }


// lock_guard
void worker4(int& result, std::mutex& m) {
    for (int i = 0; i < 100000; i++) {
        // lock 생성 시에 m.lock() 을 실행한다고 보면 된다.
        std::lock_guard<std::mutex> lock(m);
        result += 1;

        // scope 를 빠져 나가면 lock 이 소멸되면서
        // m 을 알아서 unlock 한다.
        }
    }

void main4() {
    int counter = 0;
    std::mutex m;  // 우리의 mutex 객체

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker4, std::ref(counter), std::ref(m)));
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
    }


// mutex의 lock순서는 worker내에서 동일하게 해야한다.
// lock 순서가 다르면 deadlock이 발생한다.
// deadlock : 두 개 이상의 쓰레드가 서로 lock을 기다리고 있어서, 프로그램이 멈추는 현상 
// try_lock 기능 : lock 을 시도해보고, lock 이 되지 않으면 다른 일을 수행한다.
void worker10(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 10; i++) {
        m1.lock();
        m2.lock();

        std::cout << "Worker10 Hi! " << i << std::endl; // critical section
        // 1초간 멈춤
        std::this_thread::sleep_for(std::chrono::seconds(1));
        m2.unlock();
        m1.unlock();
        }
    }

void worker11(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 10; i++) {
        while (true) {
            m1.lock();
            m2.lock();

            //// m1 이 이미 lock 되어 있다면 "야 차 빼" 를 수행하게 된다.
            //if (!m1.try_lock()) {
            //    m2.unlock();
            //    std::cout << "Worker11 Unlock " << i << std::endl; // critical section
            //    continue;
            //    }

            // 1초간 멈춤
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Worker11 Hi! " << i << std::endl; // critical section
            //m1.unlock();
            //m2.unlock();

            m2.unlock();
            m1.unlock();
            break;
            }
        }
    }

void main5() {
    std::mutex m1, m2;  // 우리의 mutex 객체

    std::thread t1(worker10, std::ref(m1), std::ref(m2));
    std::thread t2(worker11, std::ref(m1), std::ref(m2));

    t1.join();
    t2.join();

    std::cout << "끝!" << std::endl;
    }






void main() {
    main1();
    main2();
    main3();
    main4();
    main5();
	}
















