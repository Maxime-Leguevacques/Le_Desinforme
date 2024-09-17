#pragma once

#include "CoreMinimal.h"
#include "LeDesinformeGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "LeDesinformeGameState.generated.h"


UCLASS()
class LEDESINFORME_API ALeDesinformeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	int m_currentScore = 0;
	
	float m_timer = 0.f;

	ALeDesinformeGameMode* m_gameMode = nullptr;

public:
	ALeDesinformeGameState();

protected:
	virtual void BeginPlay() override;
};
