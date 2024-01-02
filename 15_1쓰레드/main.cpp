
// ������
// ����ó���� ���� ���Ǵ� ���� �⺻���� ���
// ������� ���μ��� ������ ����Ǵ� �帧�� ����
// ���μ����� �ּ� �ϳ��� �����带 ������ ������, �����尡 �ϳ��� ���μ����� �̱� ������ ���μ������ �Ѵ�.
// ������� ���μ��� ���� �����͸� �����ϸ�, ���μ��� ���� ��������� ���ÿ� ����� �� �ִ�.
// join() : �����尡 ���� ������ ��ٸ���.
// detach() : �����尡 ������ ��ٸ��� �ʴ´�.
// ������� �����ڿ��� ���۵Ǹ�, �Ҹ��ڿ��� ����ȴ�.
// race condition : ���� �����尡 ���ÿ� �����Ͽ� �����͸� ������ ��, ����ġ ���� ����� �߻��ϴ� ����
// mutex : ���� �����尡 ���ÿ� �����Ͽ� �����͸� ������ ��, �������� �ϰ����� �����ϱ� ���� ���Ǵ� ����ȭ ���
// lock_guard : mutex�� �̿��Ͽ� �������� �ϰ����� �����ϴ� ����ȭ ���

// �Լ�
// thread : �����带 �����Ѵ�.
// join : �����尡 ���� ������ ��ٸ���.
// detach : �����尡 ������ ��ٸ��� �ʴ´�.
// get_id : �������� id�� ��´�.
// this_thread::get_id : ���� �������� id�� ��´�.
// this_thread::sleep_for : ���� �����带 ��� �����.
// this_thread::yield : ���� �����带 �纸�Ѵ�.
// this_thread::hardware_concurrency : ���� �ý��ۿ��� ���ÿ� ���� ������ �������� ������ ��´�.
// std::lock_guard : mutex�� �̿��Ͽ� �������� �ϰ����� �����ϴ� ����ȭ ���





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
    printf("������ %p ���� %lld ���� %lld ���� ����� ��� : %lld \n", this_id, start, (end - 1), sum);
    }

void main1() {
    // ������ ���� : 1~1000000 vector
    const int MAX = 1000000;
    std::vector<long long> data(MAX);
    for (int i = 0; i < MAX; i++)
        data[i] = i;

    // thread�� �̿��� �� ���ϱ�
    // thread ������ �ü���� ���� �����ǹǷ�, partioal sum�� ������ ��������� �ʴ´�.
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

    // worker thread�� ���� ������(join �Ҷ�����) ��ٸ���.
    for (auto& worker : workers)
        worker.join();

    // worker thread�� ���� ��, ��� ���
    long long total = 0;
    for (int i = 0; i < NUM_OF_THRHEAD; i++)
        total += partial_sums[i];

    std::cout << "Total Sum : " << total << std::endl;

    }

// race condition
// ���� �����尡 ���ÿ� �����Ͽ� �����͸� ������ ��, ����ġ ���� ����� �߻��ϴ� ����

void worker2(int& counter) {
    for (int i = 0; i < 100000; i++) {
        counter += 1;
        }
    }

void main2() {
    int counter = 0;

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        // ���۷����� �����Ϸ��� ref �Լ��� ���ξ� �Ѵ� (���� ���� bind �Լ� ����)
        workers.push_back(std::thread(worker2, std::ref(counter)));
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter ���� �� : " << counter << std::endl;
    }


// mutex
// ���� �����尡 ���ÿ� �����Ͽ� �����͸� ������ ��, �������� �ϰ����� �����ϱ� ���� ���Ǵ� ����ȭ ���
// thread ó���� �Ϸ��� �Լ��� ���ڷ� mutex ��ü�� �����ϰ�, m.lock�� m.unlock�� �̿��Ͽ� �������� �ϰ����� �����Ѵ�.
// thread(fn, ����1, ����2(mutex& m))
// critical section : mutex�� ��ȣ�Ǵ� �ڵ� ����
// ���⼭�� result += 1 �� critical section �̴�.

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
    std::mutex m;  // �츮�� mutex ��ü

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker3, std::ref(counter), std::ref(m))); // thread (fn, ����1, ����2)
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter ���� �� : " << counter << std::endl;
    }


// lock_guard
void worker4(int& result, std::mutex& m) {
    for (int i = 0; i < 100000; i++) {
        // lock ���� �ÿ� m.lock() �� �����Ѵٰ� ���� �ȴ�.
        std::lock_guard<std::mutex> lock(m);
        result += 1;

        // scope �� ���� ������ lock �� �Ҹ�Ǹ鼭
        // m �� �˾Ƽ� unlock �Ѵ�.
        }
    }

void main4() {
    int counter = 0;
    std::mutex m;  // �츮�� mutex ��ü

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker4, std::ref(counter), std::ref(m)));
        }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
        }

    std::cout << "Counter ���� �� : " << counter << std::endl;
    }


// mutex�� lock������ worker������ �����ϰ� �ؾ��Ѵ�.
// lock ������ �ٸ��� deadlock�� �߻��Ѵ�.
// deadlock : �� �� �̻��� �����尡 ���� lock�� ��ٸ��� �־, ���α׷��� ���ߴ� ���� 
// try_lock ��� : lock �� �õ��غ���, lock �� ���� ������ �ٸ� ���� �����Ѵ�.
void worker10(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 10; i++) {
        m1.lock();
        m2.lock();

        std::cout << "Worker10 Hi! " << i << std::endl; // critical section
        // 1�ʰ� ����
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

            //// m1 �� �̹� lock �Ǿ� �ִٸ� "�� �� ��" �� �����ϰ� �ȴ�.
            //if (!m1.try_lock()) {
            //    m2.unlock();
            //    std::cout << "Worker11 Unlock " << i << std::endl; // critical section
            //    continue;
            //    }

            // 1�ʰ� ����
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
    std::mutex m1, m2;  // �츮�� mutex ��ü

    std::thread t1(worker10, std::ref(m1), std::ref(m2));
    std::thread t2(worker11, std::ref(m1), std::ref(m2));

    t1.join();
    t2.join();

    std::cout << "��!" << std::endl;
    }






void main() {
    main1();
    main2();
    main3();
    main4();
    main5();
	}
















