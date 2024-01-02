
// ������Ǯ Ŭ������ ����� ��(Work)�� ����ó�� �ϱ�
// �����带 ������ ����, ������ ������, ����� ������ ���� �����ϰ�, �ٽ� ����ϰ� �ݺ�
// ���� - �۾��� queue�� �־�ΰ�, �����尡 queue���� �۾��� �����ͼ� ����
// queue : push, pop, front, back, empty, size
// queue�� FIFO(First In First Out) ����
// queue�� pop, front, back�� �ϱ� ���� empty, size�� üũ�ؾ���

// ������Ǯ Class ����� (��, ������Ǯ �Ž�� �����)
// �ɹ� : ������Ǯ, ������, �۾�ť, cv, m, stop_all
// �Ž�� : ������, �Ҹ���, EnqueueJob, WorkerThread
// 1. ������ : ������Ǯ, ������ ���� (������ ����)
// 2. EnqueueJob : ������Ǯ�� �۾�(�Լ�)�� ����. (job push, noti-one)  job�� ���� (�����Լ�����, �������Լ�����+���ϰ�)
// 3. WorkerThread : �����尡 queue���� �۾��� �����ͼ� ���� (���, �۾���������, �۾�����)
// 4. �Ҹ��� : ������Ǯ, ������ ���� (stop_all, noti-all, join)





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

        // job �� �߰��Ѵ�.
        void EnqueueJob(std::function<void()> job); // ����, ���� ���� job�̶�� �̸��� �Լ� ����

    private:
        // �� Worker �������� ����.
        size_t num_threads_;
        // Worker �����带 �����ϴ� ����.
        std::vector<std::thread> worker_threads_;
        // ���ϵ��� �����ϴ� job ť.
        std::queue<std::function<void()>> jobs_;
        // ���� job ť�� ���� cv �� m.
        std::condition_variable cv_job_q_;
        std::mutex m_job_q_;

        // ��� ������ ����
        bool stop_all;

        // Worker ������
        void WorkerThread(); // ���ϰ� �Ű����� ���� ������ �Ѵ�.
    };

    // 1. ������Ǯ, ������ ����
    ThreadPool::ThreadPool(size_t num_threads)
        : num_threads_(num_threads), stop_all(false) {
        worker_threads_.reserve(num_threads_); // �̸� �޸𸮸� �Ҵ��صд�.
        for (size_t i = 0; i < num_threads_; ++i) {
            worker_threads_.emplace_back([this]() { this->WorkerThread(); }); // WorkerThread()�Լ��� �����Ѵ�.
        }
    }

    // 3. �� �����尡 �����ϴ� ��(����) : ��ٸ���.�� �����´�.�� �����Ѵ�.
    void ThreadPool::WorkerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(m_job_q_);
            cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
            if (stop_all && this->jobs_.empty()) {
                return;
            }

            // �� ���� job �� ����.
            std::function<void()> job = std::move(jobs_.front()); // std::move : lvalue�� rvalue�� ��ȯ, ���� �Լ� job ����
            jobs_.pop();
            lock.unlock();

            // �ش� job �� �����Ѵ� :)
            job(); // ���� �Լ� job ����
        }
    }

    ThreadPool::~ThreadPool() {
        stop_all = true;
        cv_job_q_.notify_all();

        for (auto& t : worker_threads_) { // range based for loop
            t.join();
        }
    }
    // 2. ������ Ǯ�� �۾�(�Լ�)�� ����.
    void ThreadPool::EnqueueJob(std::function<void()> job) {
        if (stop_all) {
            throw std::runtime_error("ThreadPool ��� ������");
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
    ThreadPool::ThreadPool pool(3); // ������Ǯ ���� (������ ����)
    ThreadPool::ThreadPool pool2(3); // ������Ǯ ���� (������ ����)
    ThreadPool::ThreadPool pool3(3); // ������Ǯ ���� (������ ����)


    // 10���� �۾��� ������Ǯ�� ���� pool.EnqueueJob(���� �Լ�)
    for (int i = 0; i < 10; i++) {
        pool.EnqueueJob([i]() { work(i % 3 + 1, i); }); // ������Ǯ�� �۾�(�Լ�)�� ����, �����Լ����·� �������� ��.
    }
    // 10���� �۾��� ������Ǯ�� ���� pool.EnqueueJob(���� �Լ�)
    for (int i = 0; i < 10; i++) {
        pool2.EnqueueJob([i]() { work(i % 3 + 1, i + 10); }); // ������Ǯ�� �۾�(�Լ�)�� ����, �����Լ����·� �������� ��.
    }
    // 2���� �۾��� ������Ǯ�� ���� pool.EnqueueJob(���� �Լ�)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            pool3.EnqueueJob([i, j]() { work(i % 3 + 1, i * 20 + j); }); // ������Ǯ�� �۾�(�Լ�)�� ����, �����Լ����·� �������� ��.
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

        // job �� �߰��Ѵ�.
        template <class F, class... Args> // class�� F�� , class...�� Args�� �޴´�.
        std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f, Args&&... args); // �Լ��� ���ڵ��� ������ ���۷���(&&)��...

    private:
        // �� Worker �������� ����.
        size_t num_threads_;
        // Worker �����带 �����ϴ� ����.
        std::vector<std::thread> worker_threads_;
        // ���ϵ��� �����ϴ� job ť.
        std::queue<std::function<void()>> jobs_;
        // ���� job ť�� ���� cv �� m.
        std::condition_variable cv_job_q_;
        std::mutex m_job_q_;

        // ��� ������ ����
        bool stop_all;

        // Worker ������
        void WorkerThread();
    };

    // 1. ������Ǯ, ������ ����
    ThreadPool2::ThreadPool2(size_t num_threads)
        : num_threads_(num_threads), stop_all(false) {
        worker_threads_.reserve(num_threads_);
        for (size_t i = 0; i < num_threads_; ++i) {
            worker_threads_.emplace_back([this]() { this->WorkerThread(); });
        }
    }

    // 3. �� �����尡 �����ϴ� ��(����) : ��ٸ���.�� �����´�.�� �����Ѵ�.
    void ThreadPool2::WorkerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(m_job_q_);
            cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
            if (stop_all && this->jobs_.empty()) {
                return;
            }

            // �� ���� job �� ����.
            std::function<void()> job = std::move(jobs_.front());
            jobs_.pop();
            lock.unlock();

            // �ش� job �� �����Ѵ� :)
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

    // 2. ������ Ǯ�� �۾�(�Լ�)�� ����.
    // void Ÿ���� �Լ��� ���� ��, ���ϰ��� �����Ƿ�, std::future<void>�� �����ϵ����Ͽ�, ���ϰ��� ���� �� �ֵ��� �Ѵ�.
    // std::future<void>�� ���ϰ��� ���� �Լ��� �����ϰ�, ������ �Ϸ�Ǹ�, get()�� ���� ���ϰ��� ���� �� �ִ�.
    // std::future<int>�� ���ϰ��� �ִ� �Լ��� �����ϰ�, ������ �Ϸ�Ǹ�, get()�� ���� ���ϰ��� ���� �� �ִ�.


    template <class F, class... Args> // F, Args...
    std::future<typename std::result_of<F(Args...)>::type> ThreadPool2::EnqueueJob(F&& f, Args&&... args) {
        if (stop_all) {
            throw std::runtime_error("ThreadPool ��� ������");
        }
        // �Լ��� ���� Ÿ���� �߷��ؼ� �����ϴ� ����
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

// ��� ���� (�Ű������� ���ϰ��� �ִ��Լ��� ������Ǯ�� �ִ� ����)

int work2(int t, int id) { // ���ϰ� int, �Ű����� int, int
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
    return t + id;
}

void main2() {
    // ������Ǯ ���� (������ ����)
    ThreadPool2::ThreadPool2 pool(3);

    // ���ϰ��� ���� ����
    std::vector<std::future<int>> futures;

    // 10���� �۾��� ������Ǯ�� ����  pool.EnqueueJob(fn, args...)
    for (int i = 0; i < 10; i++) {
        futures.emplace_back(pool.EnqueueJob(work2, i % 3 + 1, i)); // ������Ǯ�� �۾�(�Ϲ��Լ�)�� ����, �Ϲ��Լ�+�Ű�����
    }

    // ���(���ϰ�)�� ������. packged_task�� ���ϰ��� future�� get()�� ���� ������
    for (auto& f : futures) { // range based for loop
        printf("result : %d \n", f.get());
    }
}








void main() {
	main1();
	main2();
}