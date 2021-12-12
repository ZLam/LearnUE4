#pragma once

#include "HAL/Runnable.h"

class MULTITHREAD_API FTestInitThreadRunnable : public FRunnable
{
private:
	FRunnableThread* Thread = nullptr;

public:
	FTestInitThreadRunnable();
	virtual ~FTestInitThreadRunnable() override;

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void EnsureCompletion();
};
