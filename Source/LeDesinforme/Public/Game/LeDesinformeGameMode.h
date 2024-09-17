#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LeDesinformeGameMode.generated.h"


UCLASS()
class LEDESINFORME_API ALeDesinformeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	int m_highScore = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	float m_defaultTimerValue = 0.f;

public:
	ALeDesinformeGameMode();
	
public:
	float GetDefaultTimerValue();
};
