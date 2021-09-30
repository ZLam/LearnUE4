#pragma once

#include "HAL/Runnable.h"

class MULTITHREAD_API FTestThreadRunnable : public FRunnable
{
private:
	FThreadSafeCounter StopTaskCounter = 0;

	FRunnableThread* Thread = nullptr;

	TArray<int32> PrimeNumbers;

	int32 MaxAmount = 0;

	/**
	 * 临界区
	 * 该类型需要不同平台有不同的实现。
	 * 临界区可以理解为，一组操作或行为需要原子性执行。
	 * 那原子性又是什么，顾名思义，原子就系最细的，最小粒度，uncutable。所以一个操作，要不就没做，要不就做完，不存在中间态，做到30%这样的情况。
	 * 所以既然临界区能原子性执行一组操作，那么就能处理公共资源使用的同步问题。如果临界区没执行任何操作，那么需要进入临界区的操作可以直接进入，
	 * 直到临界区的操作做完前，其他任何需要进入临界区的操作会先挂起，当临界区空出再会调起。就是这样保证原子性的，完整做完一组操作再做其他。
	 * https://www.geeksforgeeks.org/g-fact-70/
	 * https://www.cnblogs.com/chenhs/archive/2011/06/13/2080050.html
	 *
	 * windows平台的critical section和mutex
	 * critical section通常都会比mutex快。
	 * 但critical section只能在同一进程里线程间同步。
	 * mutex可以不同进程间同步。
	 * 所以明显mutex能力比较强，目前理解就是mutex要支持不同进程间同步，所以暂用的资源，和处理的情况更复杂，所以比critical section慢。
	 * 一般情况下（就是非竞争情况，uncontention），critical section就会比mutex快，可能是处理的东西不多，当在竞争情况下（contention），
	 * 才会使用内核模式（kernel mode）进行同步
	 * https://stackoverflow.com/questions/800383/what-is-the-difference-between-mutex-and-critical-section
	 */
	FCriticalSection LockPrimeNumber;

	/**
	 * 事件
	 * 该类型需要不同平台有不同的实现。
	 * 某些事情发生的时候就发送事件（发送信号），收到事件（收到信号）的地方知道事情已经发生了那么可以做后续的处理。
	 * 一般多个线程间某个线程需要其他线程做完某些事情后才能做后续工作，那么其他线程做完这些事情后就会发送一个事件（信号），
	 * 然后收到事件（信号）的线程才开始后续其他的工作。
	 * bIsManualReset参数是是否需要手动reset，如果true，那么Trigger后，事件一直处于已发状态，直到执行Reset，才会把它设回未发状态；
	 * 如果false，那么Trigger后，事件处于已发状态，直到当某处收到事件后（Wait方法监听的地方），系统会将状态自动设回未发状态。
	 * 一般主要就用2方法，Trigger（触发，发送）和Wait（等待，监听）。
	 * Wait方法会阻塞，一般会阻塞到收到事件为止，或者传个时间参数，阻塞一段时间，期间如果收到事件，那么返回true，否则返回false。
	 *
	 * https://docs.microsoft.com/en-us/windows/win32/sync/using-event-objects
	 * https://docs.microsoft.com/en-us/previous-versions/ms959948(v=msdn.10)
	 * 1，同一个event，可以在多个地方监听（发送该事件时，收到事件是什么顺序？）
	 * 2，当要手动reset的event发送事件后，就处于已发状态。如果有多个地方监听事件，或者之后有新地方新加监听该事件，都会判定为
	 * 事件已发，事情已经发生，可以后续工作。
	 */
	FEvent* EventPause = nullptr;

	FThreadSafeBool bPause;
	
public:
	FTestThreadRunnable(const int32& InMaxAmount);
	virtual ~FTestThreadRunnable() override;
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void EnsureCompletion();

	void WaitForCompletion();

	int32 GetLastPrimeNumber();

	void Pause();

	void Resume();
};
