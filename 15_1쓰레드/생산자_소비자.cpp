
// ������ �Һ��� ����
// �����ڴ� �����͸� �����ϰ�, �Һ��ڴ� �����͸� �Һ��Ѵ�.
// �����ڴ� �����͸� ������ ��, ���۰� ���� �� ������ ��ٷ��� �ϰ�, �Һ��ڴ� �����͸� �Һ��� ��, ���۰� ��� ������ ��ٷ��� �Ѵ�.
// �����ڿ� �Һ��ڴ� ���ÿ� ����Ǿ�� �ϸ�, �����ڿ� �Һ��ڴ� ���ÿ� ����� �� ����.
// �����ڿ� �Һ��ڴ� �����͸� �����Ѵ�.
// �����ڿ� �Һ��ڴ� ���ÿ� ����Ǿ�� �ϹǷ�, �����带 �̿��Ͽ� �����Ѵ�.
// �����ڿ� �Һ��ڴ� ���ÿ� ����� �� �����Ƿ�, mutex�� �̿��Ͽ� �������� �ϰ����� �����Ѵ�.
// �����ڿ� �Һ��ڴ� �����͸� �����ϹǷ�, �����ڰ� �����͸� ������ ��, �Һ��ڰ� �����͸� �Һ����� ������ ��ٷ��� �ϰ�, �Һ��ڰ� �����͸� �Һ��� ��, �����ڰ� �����͸� �������� ������ ��ٷ��� �Ѵ�.


// �����ڿ� �Һ��ڴ� ���ÿ� ����Ǿ�� �ϹǷ�, condition variable�� �̿��Ͽ� �����ڿ� �Һ��ڰ� ���� ��ٸ��� �ִ� ��Ȳ�� �����.
// condition_variable.notify_one() : ����ϰ� �ִ� ������ �� �ϳ��� �����.
// unique_lock : unlock �Ŀ� �ٽ� lock�� �� �� �����Ƿ�, lock_guard ���� �� �����ϴ�. (lock_guard�� unlock �Ŀ� �ٽ� lock�� �� �� ����.)
// cv->wait�� unique_lock�� ����ϹǷ�, unique_lock�� ����ؾ� �Ѵ�.
// ���� �����忡�� ���� ��ü�� ���� �����Ѵٸ� Race Condition �� �߻��մϴ�. 
// �̸� �ذ��ϱ� ���ؼ��� �������� ����� ������, �� ���� ������� ���ؽ��� ����ϴ� ����� �ֽ��ϴ�. 
// ���ؽ��� �� ���� �� �����忡���� ȹ���� �� �ֽ��ϴ�. ȹ���� ���ؽ��� �ݵ�� ��ȯ�ؾ� �մϴ�. 
// lock_guard �� unique_lock ���� �̿��ϸ� ���ؽ��� ȹ��-��ȯ�� �ս��� ó���� �� �ֽ��ϴ�. 
// ���ؽ��� ����� �� ������� �߻����� �ʵ��� �����ؾ� �մϴ�. ������� ������ϴ� ���� �ſ� ��ƽ��ϴ�.
// condition_variable �� ����ϸ� ������-�Һ��� ������ ���� ������ �� �ֽ��ϴ�.


#include <chrono>              // std::chrono::miliseconds
#include <condition_variable>  // std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// critical setion, cv�� ready �Ǿ����� �˸���.
void producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int index, std::condition_variable* cv) {
    for (int i = 0; i < 5; i++) {
        // ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
        // �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "������Ʈ : " + std::to_string(i) + " from thread(" +
            std::to_string(index) + ")\n";

        // data �� ������ ���̿��� �����ǹǷ� critical section �� �־�� �Ѵ�.
        m->lock();
        downloaded_pages->push(content); // critical section
        m->unlock();

        // consumer ���� content �� �غ�Ǿ����� �˸���.
        cv->notify_one();
        }
    }

// cv�� ���(listen for lk)�ϰ�, cv�� notify_one() �Ǹ� lk�� ȹ���Ѵ�.
// ���� �ڵ带 �����ϰ�, lk�� ��ȯ�Ѵ�.
void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int* num_processed, std::condition_variable* cv) {
    while (*num_processed < 25) {
        std::unique_lock<std::mutex> lk(*m);

        // �ٿ�ε�� �������� ������ ��ٸ���.lk �� unique_lock ��ü�̴�.
        cv->wait(
            lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

        if (*num_processed == 25) {
            lk.unlock();
            return;
            }

        // �� ���� �������� �а� ��� ��Ͽ��� �����Ѵ�.
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();

        (*num_processed)++;
        lk.unlock();

        // content �� ó���Ѵ�.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
    }

int main() {
    // ���� �ٿ�ε��� �������� ����Ʈ��, ���� ó������ ���� �͵��̴�.
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::condition_variable cv;

    // 5���� ������ �����带 �����Ѵ�.
    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(
            std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
        }

    // 3���� �Һ��� �����带 �����Ѵ�.
    int num_processed = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(
            std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
        }

    // ��� ������ �����尡 ����� ������ ��ٸ���.
    for (int i = 0; i < 5; i++) {
        producers[i].join();
        }

    // ��� ������ �����尡 ����Ǿ����Ƿ�, �� �̻� �����Ͱ� ������� �ʴ´�.
    // ����, ������ �ڰ� �ִ� ��������� ��� �����. �׷��� join �� �� �ִ�.
    cv.notify_all();

    // ��� �Һ��� �����尡 ����� ������ ��ٸ���.
    for (int i = 0; i < 3; i++) {
        consumers[i].join();
        }
    }