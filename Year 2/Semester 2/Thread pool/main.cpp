#include <iostream>
#include <condition_variable>
#include <queue>
#include <thread>
#include <memory>
#include <string>

using namespace std;

template <class T>
struct Data
{
	bool ready;
	Data() : ready(false) {};
	T data;
};


typedef std::function<void()> fn_type;
class Worker
{
	bool enabled;
	condition_variable cv;
	queue <fn_type> fQueue;
	mutex mutx;
	thread thred;

	void thread_fn();

public:
	void append(fn_type fn);
	size_t getTaskCount();
	bool isEmpty();
	Worker();
	~Worker();

};

class ThreadPool
{
	typedef shared_ptr<Worker> worker_ptr;

	worker_ptr getFreeWorker();
	vector <worker_ptr> workers;

public:
	template <class R, class FN, class... ARGS>
	shared_ptr<Data<R>> runAsync(FN fn, ARGS... args)
	{
		function<R()> rFn = bind(fn, args...);
		shared_ptr<Data<R>> pData(new Data<R>());
		fn_type fnT = [=]()
		{
			pData->data = rFn();
			pData->ready = true;
		};
		auto pWorker = getFreeWorker();
		pWorker->append(fnT);
		return pData;
	}

	template <class FN, class... ARGS>
	void runAsync(FN fn, ARGS... args)
	{
		auto pWorker = getFreeWorker();
		pWorker->append(bind(fn, args...));
	}

	ThreadPool(size_t threads = 1);
};

Worker::Worker() :enabled(true), fQueue(), thred(&Worker::thread_fn, this) {};

Worker::~Worker()
{
	enabled = false;
	cv.notify_one();
	thred.join();
}

void Worker::append(fn_type fn)
{
	unique_lock <mutex> locker(mutx);
	fQueue.push(fn);
	cv.notify_one();
}

size_t Worker::getTaskCount()
{
	unique_lock <mutex> locker(mutx);
	return fQueue.size();
}

bool Worker::isEmpty()
{
	unique_lock <mutex> locker(mutx);
	return fQueue.empty();
}

void Worker::thread_fn()
{
	while (enabled)
	{
		unique_lock <mutex> locker(mutx);

		//wait for free thread
		cv.wait(locker, [&]() {return !fQueue.empty() || !enabled; });

		while (!fQueue.empty())
		{
			fn_type fn = fQueue.front();
			locker.unlock();
			fn();
			locker.lock();
			fQueue.pop();
		}
	}
}


ThreadPool::ThreadPool(size_t threads)
{
	if (threads == 0)
		threads = 1;
	for (size_t i = 0; i < threads; i++)
	{
		worker_ptr pWorker(new Worker);
		workers.push_back(pWorker);
	}
}

ThreadPool::worker_ptr ThreadPool::getFreeWorker()
{
	worker_ptr pWorker;
	size_t minTasks = UINT32_MAX;
	for (auto &it : workers)
	{
		if (it->isEmpty())
		{
			return it;
		}
		else if (minTasks > it->getTaskCount())
		{
			minTasks = it->getTaskCount();
			pWorker = it;
		}
	}
	return pWorker;
}

double foo()
{
	return 14.5;
}

int sum(int a, int b)
{
	return a + b;
}
string myFn(int a, int b)
{
	string str = "String = " + to_string(a) + " " + to_string(b);
	return str;
}

void main()
{
	ThreadPool pool(4);

	auto r1 = pool.runAsync<double>(&foo);
	auto r2 = pool.runAsync<int>(&sum, 100, 54);
	auto r3 = pool.runAsync<bool>([]() { return true; });
	auto r4 = pool.runAsync<string>(myFn, 50, 20);

	while (!r1->ready);
	cout << r1->data << endl;
	while (!r2->ready);
	cout << r2->data << endl;
	while (!r3->ready);
	cout << r3->data << endl;
	while (!r4->ready);
	cout << r4->data << endl;
	system("pause");
}