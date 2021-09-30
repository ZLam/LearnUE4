#include "NormalSingleton.h"

FNormalSingleton::FNormalSingleton()
{
	
}

FNormalSingleton::~FNormalSingleton()
{
	
}

FNormalSingleton& FNormalSingleton::Get()
{
	static FNormalSingleton Instance{};
	return Instance;
}
