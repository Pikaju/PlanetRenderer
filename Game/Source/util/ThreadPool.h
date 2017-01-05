#pragma once

#include <thread>
#include <vector>

class Task
{
public:
	Task(void(*function)(void*), void* parameters) : m_function(function), m_parameters(parameters), m_completed(false) {  }
	Task() : m_function(nullptr), m_parameters(nullptr), m_completed(true) {  }
	inline void execute() { m_function(m_parameters); m_completed = true; }
	inline bool isCompleted() const { return m_completed; }
private:
	void(*m_function)(void*);
	void* m_parameters;
	bool m_completed;
};

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void startThreads(unsigned int numThreads);
	void stopThreads();

	bool isSaturated() const;
	void addTask(const Task& task);

	inline bool isRunning() const { return m_running; }
protected:
	inline Task& getTask(unsigned int index) { return m_tasks[index]; }

	static void workerThread(ThreadPool* threadPool, unsigned int id);
private:
	bool m_running;
	std::vector<std::thread> m_threads;
	std::vector<Task> m_tasks;
};

