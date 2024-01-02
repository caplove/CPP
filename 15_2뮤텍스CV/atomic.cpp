


// mutex�� atomic ��
// mutex�� lock�� unlock�� ����Ͽ� �浹�� ����
// atomic�� lock�� unlock�� ������� �ʰ�, ���������� �浹�� ���� 
// (counter++ ������ ���� ������ �ٸ� �����尡 �������� ���ϵ��� �� == counter++������ �ѹ��� �̷�����ٴ� �ǹ�!)
// atomic�� mutex���� ������
// atomic�� ������ ���� ���길 ����
// mutex�� ������ ���� ���� �Ӹ� �ƴ϶� ������ �ڵ带 ��� ����
// atomic�� ������ ���� ������ ������ ������ ������ ���� ������ ���� ��� ���
// store �� load �� atomic ��ü�鿡 ���ؼ� ���������� ����� �б⸦ �������ִ� �Լ� �Դϴ�. 
// �� ��, �߰����� ���ڷ�, ��� ���·� memory_order �� ������ ������ ������ �� �ִµ�, 
// �̴� atomic ��ü�鿡 ���� ������ ��� ������ �̷������ �ϴ����� �������ִ� ���Դϴ�.
// memory_order_relaxed : relaxed ordering (���� ���� X)
// memory_order_consume : consume ordering (���� ���� X)
// memory_order_acquire : acquire ordering (���� ���� O)
// memory_order_release : release ordering (���� ���� O)
// memory_order_acq_rel : acquire-release ordering (���� ���� O)
// memory_order_seq_cst : sequential consistency ordering (���� ���� O)

//���� - ���� memory order
//����(store)
//memory_order_relaxed, memory_order_release, memory_order_seq_cst

//�б�(load)
//memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_seq_cst

//�а� - �����ϰ� - ����(read - modify - write)
//memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_release, memory_order_acq_rel, memory_order_seq_cst

// mutex�� ����� �浹 ���� (������� ������, counter�� ���� 400000���� �۰� ����)
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

    std::cout << "Counter ���� �� : " << counter << std::endl;
}



// atomic�� ����� �浹 ����
#include <atomic>

void worker2(std::atomic<int>& counter) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
}

void main2() {
    std::atomic<int> counter(0); // atomic ���� ����, �ʱⰪ 0

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker2, ref(counter)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter ���� �� : " << counter << std::endl;
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
    // data �� �غ�� �� ���� ��ٸ���.
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