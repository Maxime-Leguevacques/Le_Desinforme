#include "Game/LeDesinformeGameInstance.h"


ULeDesinformeGameInstance::ULeDesinformeGameInstance()
{
	
}

void ULeDesinformeGameInstance::Init()
{
	Super::Init();
}

int ULeDesinformeGameInstance::GetScore() const
{
	return m_score;
}

void ULeDesinformeGameInstance::SetScore(const int _score)
{
	m_score = _score;
}