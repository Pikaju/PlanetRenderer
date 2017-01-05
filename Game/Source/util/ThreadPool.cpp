#include "ThreadPool.h"

#include "../debug/Debug.h"

ThreadPool::ThreadPool() : m_running(false), m_threads(), m_tasks()
{
}

ThreadPool::~ThreadPool()
{
	stopThreads();
}

void ThreadPool::startThreads(unsigned int numThreads)
{
	m_running = true;
	m_threads.reserve(numThreads);
	m_tasks.resize(numThreads);
	for (unsigned int i = 0; i < numThreads; i++) {
		m_threads.emplace_back(workerThread, this, i);
	}
}

void ThreadPool::stopThreads()
{
	m_running = false;
	for (unsigned int i = 0; i < m_threads.size(); i++) {
		m_threads[i].join();
	}
	m_threads.clear();
	m_tasks.clear();
}

bool ThreadPool::isSaturated() const
{
	for (unsigned int i = 0; i < m_tasks.size(); i++) {
		if (m_tasks[i].isCompleted()) return false;
	}
	return true;
}

void ThreadPool::addTask(const Task& task)
{
	for (unsigned int i = 0; i < m_tasks.size(); i++) {
		if (m_tasks[i].isCompleted()) {
			m_tasks[i] = task;
			return;
		}
	}
	Debug::crash("Every thread saturated");
}

void ThreadPool::workerThread(ThreadPool* threadPool, unsigned int id)
{
	while (threadPool->isRunning()) {
		if (!threadPool->getTask(id).isCompleted()) {
			threadPool->getTask(id).execute();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}