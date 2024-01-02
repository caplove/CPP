


// mutex와 atomic 비교
// mutex는 lock과 unlock을 사용하여 충돌을 방지
// atomic은 lock과 unlock을 사용하지 않고, 내부적으로 충돌을 방지 
// (counter++ 연산이 끝날 때까지 다른 쓰레드가 접근하지 못하도록 함 == counter++동작이 한번에 이루어진다는 의미!)
// atomic은 mutex보다 빠르다
// atomic은 변수에 대한 연산만 가능
// mutex는 변수에 대한 연산 뿐만 아니라 임의의 코드를 사용 가능
// atomic은 변수에 대한 연산이 빠르기 때문에 변수에 대한 연산이 많은 경우 사용
// store 과 load 는 atomic 객체들에 대해서 원자적으로 쓰기와 읽기를 지원해주는 함수 입니다. 
// 이 때, 추가적인 인자로, 어떠한 형태로 memory_order 을 지정할 것인지 전달할 수 있는데, 
// 이는 atomic 객체들에 대한 연산이 어떠한 순서로 이루어져야 하는지를 지정해주는 것입니다.
// memory_order_relaxed : relaxed ordering (순서 보장 X)
// memory_order_consume : consume ordering (순서 보장 X)
// memory_order_acquire : acquire ordering (순서 보장 O)
// memory_order_release : release ordering (순서 보장 O)
// memory_order_acq_rel : acquire-release ordering (순서 보장 O)
// memory_order_seq_cst : sequential consistency ordering (순서 보장 O)

//연산 - 허용된 memory order
//쓰기(store)
//memory_order_relaxed, memory_order_release, memory_order_seq_cst

//읽기(load)
//memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_seq_cst

//읽고 - 수정하고 - 쓰기(read - modify - write)
//memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_release, memory_order_acq_rel, memory_order_seq_cst

// mutex를 사용한 충돌 방지 (사용하지 않으면, counter의 값이 400000보다 작게 나옴)
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void worker1(int& counter) {
    for (int i = 0; i < 100000; i++) {
        //mtx.lock();
        counter++;
        //mtx.unlock();
    }
}

void main1() {
    int counter = 0;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker1, std::ref(counter)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
}



// atomic을 사용한 충돌 방지
#include <atomic>

void worker2(std::atomic<int>& counter) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
}

void main2() {
    std::atomic<int> counter(0); // atomic 변수 선언, 초기값 0

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker2, ref(counter)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
}

using std::memory_order_relaxed;

std::atomic<bool> is_ready;
std::atomic<int> data[3];

void producer() {
    data[0].store(1, memory_order_relaxed);
    data[1].store(2, memory_order_relaxed);
    data[2].store(3, memory_order_relaxed);
    is_ready.store(true, std::memory_order_release);
}

void consumer() {
    // data 가 준비될 때 까지 기다린다.
    while (!is_ready.load(std::memory_order_acquire)) {
    }

    std::cout << "data[0] : " << data[0].load(memory_order_relaxed) << std::endl;
    std::cout << "data[1] : " << data[1].load(memory_order_relaxed) << std::endl;
    std::cout << "data[2] : " << data[2].load(memory_order_relaxed) << std::endl;
}

void main3() {
    std::vector<std::thread> threads;

    threads.push_back(std::thread(producer));
    threads.push_back(std::thread(consumer));

    for (int i = 0; i < 2; i++) {
        threads[i].join();
    }
}

void main() {
    main1();
    main2();
    main3();
};