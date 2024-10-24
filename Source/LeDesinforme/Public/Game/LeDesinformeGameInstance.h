#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LeDesinformeGameInstance.generated.h"


UENUM(BlueprintType)
enum EGameState
{
	HomeMenu	UMETA(DisplayName = "HomeMenu"),
	Playing		UMETA(DisplayName = "Playing"),
	PauseMenu	UMETA(DisplayName = "PauseMenu"),
	WinMenu		UMETA(DisplayName = "WinMenu"),
	GameOverMenu UMETA(DisplayName = "GameOverMenu"),
	EndGameMenu	UMETA(DisplayName = "EndGameMenu")
};


UCLASS()
class LEDESINFORME_API ULeDesinformeGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	int m_score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EGameState> m_currentGameState;
	
public:
	ULeDesinformeGameInstance();

public:
	virtual void Init() override;
	void OnGameStateChange();

	int GetScore() const;
	EGameState GetGameState() const;
	
	void SetScore(const int _score);
	void SetGameState(EGameState _gameState);
};
