#pragma once

class MULTITHREAD_API FNormalSingleton
{
private:
	FNormalSingleton();
	virtual ~FNormalSingleton();

	int32 NonSyncCounter;
	
public:
	static FNormalSingleton& Get();

	void IncreaseNonSyncCounter()
	{
		++NonSyncCounter;
	}

	void ResetNonSyncCounter()
	{
		NonSyncCounter = 0;
	}

	int32 GetNonSyncCounter()
	{
		return NonSyncCounter;
	}
};
