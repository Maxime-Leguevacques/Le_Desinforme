#include "Game/LeDesinformeGameState.h"

#include "Game/LeDesinformeGameMode.h"
#include "Kismet/GameplayStatics.h"


ALeDesinformeGameState::ALeDesinformeGameState()
{
	
}

void ALeDesinformeGameState::BeginPlay()
{
	Super::BeginPlay();

	m_gameMode = Cast<ALeDesinformeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	m_timer = m_gameMode->GetDefaultTimerValue();
}
