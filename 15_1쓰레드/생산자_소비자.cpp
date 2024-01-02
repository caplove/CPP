
// 생산자 소비자 문제
// 생산자는 데이터를 생산하고, 소비자는 데이터를 소비한다.
// 생산자는 데이터를 생산할 때, 버퍼가 가득 차 있으면 기다려야 하고, 소비자는 데이터를 소비할 때, 버퍼가 비어 있으면 기다려야 한다.
// 생산자와 소비자는 동시에 실행되어야 하며, 생산자와 소비자는 동시에 실행될 수 없다.
// 생산자와 소비자는 데이터를 공유한다.
// 생산자와 소비자는 동시에 실행되어야 하므로, 쓰레드를 이용하여 구현한다.
// 생산자와 소비자는 동시에 실행될 수 없으므로, mutex를 이용하여 데이터의 일관성을 보장한다.
// 생산자와 소비자는 데이터를 공유하므로, 생산자가 데이터를 생산할 때, 소비자가 데이터를 소비하지 않으면 기다려야 하고, 소비자가 데이터를 소비할 때, 생산자가 데이터를 생산하지 않으면 기다려야 한다.


// 생산자와 소비자는 동시에 실행되어야 하므로, condition variable을 이용하여 생산자와 소비자가 서로 기다리고 있는 상황을 만든다.
// condition_variable.notify_one() : 대기하고 있는 쓰레드 중 하나를 깨운다.
// unique_lock : unlock 후에 다시 lock을 걸 수 있으므로, lock_guard 보다 더 유연하다. (lock_guard는 unlock 후에 다시 lock을 걸 수 없다.)
// cv->wait가 unique_lock을 사용하므로, unique_lock을 사용해야 한다.
// 여러 쓰레드에서 같은 객체의 값을 수정한다면 Race Condition 이 발생합니다. 
// 이를 해결하기 위해서는 여러가지 방법이 있지만, 한 가지 방법으로 뮤텍스를 사용하는 방법이 있습니다. 
// 뮤텍스는 한 번에 한 쓰레드에서만 획득할 수 있습니다. 획득한 뮤텍스는 반드시 반환해야 합니다. 
// lock_guard 나 unique_lock 등을 이용하면 뮤텍스의 획득-반환을 손쉽게 처리할 수 있습니다. 
// 뮤텍스를 사용할 때 데드락이 발생하지 않도록 주의해야 합니다. 데드락을 디버깅하는 것은 매우 어렵습니다.
// condition_variable 을 사용하면 생산자-소비자 패턴을 쉽게 구현할 수 있습니다.


#include <chrono>              // std::chrono::miliseconds
#include <condition_variable>  // std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// critical setion, cv로 ready 되었음을 알린다.
void producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int index, std::condition_variable* cv) {
    for (int i = 0; i < 5; i++) {
        // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
        // 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
            std::to_string(index) + ")\n";

        // data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
        m->lock();
        downloaded_pages->push(content); // critical section
        m->unlock();

        // consumer 에게 content 가 준비되었음을 알린다.
        cv->notify_one();
        }
    }

// cv로 대기(listen for lk)하고, cv가 notify_one() 되면 lk를 획득한다.
// 다음 코드를 실행하고, lk를 반환한다.
void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int* num_processed, std::condition_variable* cv) {
    while (*num_processed < 25) {
        std::unique_lock<std::mutex> lk(*m);

        // 다운로드된 페이지가 없으면 기다린다.lk 는 unique_lock 객체이다.
        cv->wait(
            lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

        if (*num_processed == 25) {
            lk.unlock();
            return;
            }

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();

        (*num_processed)++;
        lk.unlock();

        // content 를 처리한다.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
    }

int main() {
    // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::condition_variable cv;

    // 5개의 생산자 쓰레드를 생성한다.
    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(
            std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
        }

    // 3개의 소비자 쓰레드를 생성한다.
    int num_processed = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(
            std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
        }

    // 모든 생산자 쓰레드가 종료될 때까지 기다린다.
    for (int i = 0; i < 5; i++) {
        producers[i].join();
        }

    // 모든 생산자 쓰레드가 종료되었으므로, 더 이상 데이터가 생산되지 않는다.
    // 따라서, 나머지 자고 있는 쓰레드들을 모두 깨운다. 그래야 join 할 수 있다.
    cv.notify_all();

    // 모든 소비자 쓰레드가 종료될 때까지 기다린다.
    for (int i = 0; i < 3; i++) {
        consumers[i].join();
        }
    }