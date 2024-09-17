#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LeDesinformeGameMode.generated.h"


UCLASS()
class LEDESINFORME_API ALeDesinformeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float m_defaultTimerValue = 0.f;

public:
	ALeDesinformeGameMode();

protected:
	virtual void BeginPlay() override;
	
public:
	float GetDefaultTimerValue();
	// When Player reports a bad Employee
	void Win();
	// When Player reports a good Employee
	void GameOver();
	// When game timer runs out
	void EndGame();
};
