#include "Game/PlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "Game/LeDesinformeGameInstance.h"
#include "Game/LeDesinformeGameState.h"
#include "UI/Widget_HUD.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	if (gameInstance->GetGameState() == EGameState::Playing && m_widgetHudClass)
	{
		m_widgetHudInstance = CreateWidget<UUserWidget>(GetWorld(), m_widgetHudClass);
		if (m_widgetHudInstance)
		{
			m_widgetHudInstance->AddToViewport();
		}

		// Update HUD in the BeginPlay since when a new round starts, map is reloaded and HUD is reloaded as well, setting score to 0
		this->UpdateScore();
	}
}

void APlayerHUD::UpdateTimer()
{
	if (m_widgetHudInstance)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_widgetHudInstance))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateTimer(gameState->GetTimer());
		}
	}
}

void APlayerHUD::UpdateScore()
{
	if (m_widgetHudInstance)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_widgetHudInstance))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateScore(gameState->GetScore());
		}
	}
}
