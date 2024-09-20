#include "Game/LeDesinformeGameMode.h"

#include "Game/LeDesinformeGameInstance.h"
#include "Game/LeDesinformeGameState.h"
#include "Kismet/GameplayStatics.h"


ALeDesinformeGameMode::ALeDesinformeGameMode()
{
	
}

void ALeDesinformeGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get score from game instance when new round begins.
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	gameState->SetScore(gameInstance->GetScore());
}

float ALeDesinformeGameMode::GetDefaultTimerValue()
{
	return m_defaultTimerValue; 
}

void ALeDesinformeGameMode::OnGameStateChange()
{
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	switch (gameState->GetCurrentGameState())
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

void ALeDesinformeGameMode::Win()
{
	// Increment Score and do all high score updates and checks.
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	gameState->IncrementScore();
	// Reopen the level
	UGameplayStatics::OpenLevel(this, "LevelOffice");
}

void ALeDesinformeGameMode::GameOver()		// TODO
{
	
}
 
void ALeDesinformeGameMode::EndGame()		// TODO
{
	
}
