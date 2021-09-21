#include "HAL/Runnable.h"

class FTestThreadRunnable : public FRunnable
{
private:
	FThreadSafeCounter StopTaskCounter = 0;

	FRunnableThread* Thread = nullptr;

	TArray<int32> PrimeNumbers;

	int32 MaxAmount = 0;

	/**
	 * 临界区
	 * 该类型需要不同平台有不同的实现。
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
