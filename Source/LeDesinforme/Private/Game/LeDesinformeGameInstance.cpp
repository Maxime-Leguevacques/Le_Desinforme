#include "Game/LeDesinformeGameInstance.h"

#include "Kismet/GameplayStatics.h"


ULeDesinformeGameInstance::ULeDesinformeGameInstance()
{
}

void ULeDesinformeGameInstance::Init()
{
	Super::Init();
	SetGameState(EGameState::HomeMenu);
}

void ULeDesinformeGameInstance::OnGameStateChange()
{
	switch (m_currentGameState)
	{
	case EGameState::HomeMenu:
		UGameplayStatics::OpenLevel(this, "LevelHomeMenu");
		break;
	case EGameState::Playing:
		UGameplayStatics::OpenLevel(this, "LevelOffice");
		break;
	case EGameState::PauseMenu:
		break;
	case EGameState::WinMenu:
		break;
	case EGameState::GameOverMenu:
		break;
	case EGameState::EndGameMenu:
		break;
	}
}

int ULeDesinformeGameInstance::GetScore() const
{
	return m_score;
}

EGameState ULeDesinformeGameInstance::GetGameState() const
{
	return m_currentGameState;
}

void ULeDesinformeGameInstance::SetScore(const int _score)
{
	m_score = _score;
}

void ULeDesinformeGameInstance::SetGameState(EGameState _gameState)
{
	m_currentGameState = _gameState;
	OnGameStateChange();
}
