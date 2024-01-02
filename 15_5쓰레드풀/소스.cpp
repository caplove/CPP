
// 쓰레드풀 클래스를 만들어 일(Work)을 병렬처리 하기
// 쓰레드를 여러개 만들어서, 할일이 있으면, 대기중 쓰레드 깨워 실행하고, 다시 대기하고를 반복
// 원리 - 작업을 queue에 넣어두고, 쓰레드가 queue에서 작업을 가져와서 실행
// queue : push, pop, front, back, empty, size
// queue는 FIFO(First In First Out) 구조
// queue는 pop, front, back을 하기 전에 empty, size를 체크해야함

// 쓰레드풀 Class 만들기 (즉, 쓰레드풀 매쏘드 만들기)
// 맴버 : 쓰레드풀, 쓰레드, 작업큐, cv, m, stop_all
// 매쏘드 : 생성자, 소멸자, EnqueueJob, WorkerThread
// 1. 생성자 : 쓰레드풀, 쓰레드 생성 (쓰레드 개수)
// 2. EnqueueJob : 쓰레드풀에 작업(함수)를 넣음. (job push, noti-one)  job의 형태 (람다함수형태, 임의의함수형태+리턴값)
// 3. WorkerThread : 쓰레드가 queue에서 작업을 가져와서 실행 (대기, 작업가져오기, 작업실행)
// 4. 소멸자 : 쓰레드풀, 쓰레드 종료 (stop_all, noti-all, join)





#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


namespace ThreadPool {

    class ThreadPool {
    public:
        ThreadPool(size_t num_threads);
        ~ThreadPool();

        // job 을 추가한다.
        void EnqueueJob(std::function<void()> job); // 리턴, 인자 없는 job이라는 이름의 함수 선언

    private:
        // 총 Worker 쓰레드의 개수.
        size_t num_threads_;
        // Worker 쓰레드를 보관하는 벡터.
        std::vector<std::thread> worker_threads_;
        // 할일들을 보관하는 job 큐.
        std::queue<std::function<void()>> jobs_;
        // 위의 job 큐를 위한 cv 와 m.
        std::condition_variable cv_job_q_;
        std::mutex m_job_q_;

        // 모든 쓰레드 종료
        bool stop_all;

        // Worker 쓰레드
        void WorkerThread(); // 리턴과 매개변수 없이 만들어야 한다.
    };

    // 1. 쓰레드풀, 쓰레드 생성
    ThreadPool::ThreadPool(size_t num_threads)
        : num_threads_(num_threads), stop_all(false) {
        worker_threads_.reserve(num_threads_); // 미리 메모리를 할당해둔다.
        for (size_t i = 0; i < num_threads_; ++i) {
            worker_threads_.emplace_back([this]() { this->WorkerThread(); }); // WorkerThread()함수를 실행한다.
        }
    }

    // 3. 각 쓰레드가 실행하는 일(동작) : 기다린다.일 가져온다.일 실행한다.
    void ThreadPool::WorkerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(m_job_q_);
            cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
            if (stop_all && this->jobs_.empty()) {
                return;
            }

            // 맨 앞의 job 을 뺀다.
            std::function<void()> job = std::move(jobs_.front()); // std::move : lvalue를 rvalue로 변환, 람다 함수 job 선언
            jobs_.pop();
            lock.unlock();

            // 해당 job 을 수행한다 :)
            job(); // 람다 함수 job 실행
        }
    }

    ThreadPool::~ThreadPool() {
        stop_all = true;
        cv_job_q_.notify_all();

        for (auto& t : worker_threads_) { // range based for loop
            t.join();
        }
    }
    // 2. 쓰레드 풀에 작업(함수)를 넣음.
    void ThreadPool::EnqueueJob(std::function<void()> job) {
        if (stop_all) {
            throw std::runtime_error("ThreadPool 사용 중지됨");
        }
        {
            std::lock_guard<std::mutex> lock(m_job_q_);
            jobs_.push(std::move(job));
        }
        cv_job_q_.notify_one();
    }

}  // namespace ThreadPool

void work(int t, int id) {
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
}


void main1() {
    ThreadPool::ThreadPool pool(3); // 쓰레드풀 생성 (쓰레드 개수)
    ThreadPool::ThreadPool pool2(3); // 쓰레드풀 생성 (쓰레드 개수)
    ThreadPool::ThreadPool pool3(3); // 쓰레드풀 생성 (쓰레드 개수)


    // 10개의 작업을 쓰레드풀에 넣음 pool.EnqueueJob(람다 함수)
    for (int i = 0; i < 10; i++) {
        pool.EnqueueJob([i]() { work(i % 3 + 1, i); }); // 쓰레드풀에 작업(함수)를 넣음, 람다함수형태로 만들어줘야 함.
    }
    // 10개의 작업을 쓰레드풀에 넣음 pool.EnqueueJob(람다 함수)
    for (int i = 0; i < 10; i++) {
        pool2.EnqueueJob([i]() { work(i % 3 + 1, i + 10); }); // 쓰레드풀에 작업(함수)를 넣음, 람다함수형태로 만들어줘야 함.
    }
    // 2차원 작업을 쓰레드풀에 넣음 pool.EnqueueJob(람다 함수)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            pool3.EnqueueJob([i, j]() { work(i % 3 + 1, i * 20 + j); }); // 쓰레드풀에 작업(함수)를 넣음, 람다함수형태로 만들어줘야 함.
        }

    }
}


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


#include <chrono>
#include <condition_variable>4
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace ThreadPool2 {
    class ThreadPool2 {
    public:
        ThreadPool2(size_t num_threads);
        ~ThreadPool2();

        // job 을 추가한다.
        template <class F, class... Args> // class는 F로 , class...은 Args로 받는다.
        std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f, Args&&... args); // 함수의 인자들을 우측값 레퍼런스(&&)로...

    private:
        // 총 Worker 쓰레드의 개수.
        size_t num_threads_;
        // Worker 쓰레드를 보관하는 벡터.
        std::vector<std::thread> worker_threads_;
        // 할일들을 보관하는 job 큐.
        std::queue<std::function<void()>> jobs_;
        // 위의 job 큐를 위한 cv 와 m.
        std::condition_variable cv_job_q_;
        std::mutex m_job_q_;

        // 모든 쓰레드 종료
        bool stop_all;

        // Worker 쓰레드
        void WorkerThread();
    };

    // 1. 쓰레드풀, 쓰레드 생성
    ThreadPool2::ThreadPool2(size_t num_threads)
        : num_threads_(num_threads), stop_all(false) {
        worker_threads_.reserve(num_threads_);
        for (size_t i = 0; i < num_threads_; ++i) {
            worker_threads_.emplace_back([this]() { this->WorkerThread(); });
        }
    }

    // 3. 각 쓰레드가 실행하는 일(동작) : 기다린다.일 가져온다.일 실행한다.
    void ThreadPool2::WorkerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(m_job_q_);
            cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
            if (stop_all && this->jobs_.empty()) {
                return;
            }

            // 맨 앞의 job 을 뺀다.
            std::function<void()> job = std::move(jobs_.front());
            jobs_.pop();
            lock.unlock();

            // 해당 job 을 수행한다 :)
            job();
        }
    }

    ThreadPool2::~ThreadPool2() {
        stop_all = true;
        cv_job_q_.notify_all();

        for (auto& t : worker_threads_) {
            t.join();
        }
    }

    // 2. 쓰레드 풀에 작업(함수)를 넣음.
    // void 타입의 함수를 넣을 때, 리턴값이 없으므로, std::future<void>를 리턴하도록하여, 리턴값을 받을 수 있도록 한다.
    // std::future<void>는 리턴값이 없는 함수를 실행하고, 실행이 완료되면, get()을 통해 리턴값을 받을 수 있다.
    // std::future<int>는 리턴값이 있는 함수를 실행하고, 실행이 완료되면, get()을 통해 리턴값을 받을 수 있다.


    template <class F, class... Args> // F, Args...
    std::future<typename std::result_of<F(Args...)>::type> ThreadPool2::EnqueueJob(F&& f, Args&&... args) {
        if (stop_all) {
            throw std::runtime_error("ThreadPool 사용 중지됨");
        }
        // 함수의 리턴 타입을 추론해서 저장하는 변수
        using return_type = typename std::result_of<F(Args...)>::type;

        // Create a packaged task that wraps the function and its arguments.
        // A packaged task is a type that packages a function to store its return value.
        // This allows the return value to be retrieved asynchronously via a std::future object.
        auto job = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        // Get a std::future object associated with the result of the packaged task.
        std::future<return_type> job_result_future = job->get_future();

        // Lock the job queue and add the job to it.
        {
            std::lock_guard<std::mutex> lock(m_job_q_);
            jobs_.push([job]() { (*job)(); });
        }

        // Notify one waiting thread that there is a new job in the queue.
        cv_job_q_.notify_one();

        // Return the std::future object. It will hold the result of the function once it finishes execution.
        return job_result_future;
    }

}  // namespace ThreadPool

// 사용 예시 (매개변수와 리턴값이 있는함수를 쓰레드풀에 넣는 예시)

int work2(int t, int id) { // 리턴값 int, 매개변수 int, int
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
    return t + id;
}

void main2() {
    // 쓰레드풀 생성 (쓰레드 개수)
    ThreadPool2::ThreadPool2 pool(3);

    // 리턴값을 받을 변수
    std::vector<std::future<int>> futures;

    // 10개의 작업을 쓰레드풀에 넣음  pool.EnqueueJob(fn, args...)
    for (int i = 0; i < 10; i++) {
        futures.emplace_back(pool.EnqueueJob(work2, i % 3 + 1, i)); // 쓰레드풀에 작업(일반함수)를 넣음, 일반함수+매개변수
    }

    // 결과(리턴값)을 가져옴. packged_task의 리턴값인 future를 get()을 통해 가져옴
    for (auto& f : futures) { // range based for loop
        printf("result : %d \n", f.get());
    }
}








void main() {
	main1();
	main2();
}