#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LeDesinformeGameState.generated.h"


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
	
	void SetScore(int _score);
};
