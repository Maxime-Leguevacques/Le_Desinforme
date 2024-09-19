#include "Game/LeDesinformeGameState.h"

#include "Game/LeDesinformeGameInstance.h"
#include "Game/LeDesinformeGameMode.h"
#include "Game/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"


const FString HIGH_SCORE_FILE_NAME = "HighScore.txt";


ALeDesinformeGameState::ALeDesinformeGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	m_saveFilePath = FPaths::ProjectSavedDir() + HIGH_SCORE_FILE_NAME;
}

void ALeDesinformeGameState::BeginPlay()
{
	Super::BeginPlay();
	
	LoadHighScore();
	
	ALeDesinformeGameMode* gameMode = Cast<ALeDesinformeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	m_timer = gameMode->GetDefaultTimerValue();
}

void ALeDesinformeGameState::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);

	m_timer -= _deltaSeconds;

	// Update the HUD
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		APlayerHUD* hud = Cast<APlayerHUD>(playerController->GetHUD());
		if (hud)
		{
			hud->UpdateTimer();
		}
	}
	
	if (GEngine)
	{
		// Print timer
		FString messageTimer = FString::Printf(TEXT("TIMER : %f"), m_timer);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, messageTimer);
		// Print score
		FString messageScore = FString::Printf(TEXT("SCORE : %d"), m_score);
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, messageScore);
		// Print high score
		FString messageHighScore = FString::Printf(TEXT("HIGH SCORE : %d"), m_highScore);
		GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Green, messageHighScore);
	}

	if (m_timer <= 0.f)
	{
		ALeDesinformeGameMode* gameMode = Cast<ALeDesinformeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		gameMode->Win();
	}
}

void ALeDesinformeGameState::IncrementScore()
{
	m_score++;
	// Save score in the GameInstance
	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	gameInstance->SetScore(m_score);
	CheckHighScore();
}

void ALeDesinformeGameState::CheckHighScore()
{
	if (m_score > m_highScore)
	{
		m_highScore = m_score;
		SaveHighScore();
	}
}

void ALeDesinformeGameState::SaveHighScore()
{
	FString highScoreString = FString::FromInt(m_highScore);
	FFileHelper::SaveStringToFile(highScoreString, *m_saveFilePath);
}

void ALeDesinformeGameState::LoadHighScore()
{
	FString loadedHighScore;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*m_saveFilePath))
	{
		if (FFileHelper::LoadFileToString(loadedHighScore, *m_saveFilePath))
		{
			m_highScore = FCString::Atoi(*loadedHighScore);
		}
	}
}

int ALeDesinformeGameState::GetScore()
{
	return m_score;
}

void ALeDesinformeGameState::SetScore(int _score)
{
	m_score = _score;
}

float ALeDesinformeGameState::GetTimer()
{
	return m_timer;
}
