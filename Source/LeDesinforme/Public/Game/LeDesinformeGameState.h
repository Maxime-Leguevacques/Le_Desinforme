#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LeDesinformeGameState.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
	HomeMenu	UMETA(DisplayName = "HomeMenu"),
	Playing		UMETA(DisplayName = "Playing"),
	PauseMenu	UMETA(DisplayName = "PauseMenu"),
	WinMenu		UMETA(DisplayName = "WinMenu"),
	GameOverMenu UMETA(DisplayName = "GameOverMenu"),
	EndGameMenu	UMETA(DisplayName = "EndGameMenu")
};


UCLASS()
class LEDESINFORME_API ALeDesinformeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	int m_score = 0;
	int m_highScore = 0;
	float m_timer = 0.f;

	// For saving the highscore
	FString m_saveFilePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState", meta = (AllowPrivateAccess = "true"))
	EGameState m_currentGameState;

public:
	ALeDesinformeGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _deltaSeconds) override;

public:
	void IncrementScore();
	void CheckHighScore();
	void SaveHighScore();
	void LoadHighScore();

	int GetScore();
	float GetTimer();
	EGameState GetCurrentGameState();
	
	void SetScore(int _score);
	void SetGameState(EGameState _gameState);
};
