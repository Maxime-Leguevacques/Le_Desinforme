#include "Game/PlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "Game/LeDesinformeGameState.h"
#include "UI/Widget_HUD.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (m_selectedWidgetHud)
	{
		m_widgetHud = CreateWidget<UUserWidget>(GetWorld(), m_selectedWidgetHud);
		if (m_widgetHud)
		{
			m_widgetHud->AddToViewport();
		}

		// Update HUD in the BeginPlay since when a new round starts, map is reloaded and HUD is reloaded as well, setting score to 0
		this->UpdateScore();
	}
}

void APlayerHUD::UpdateTimer()
{
	if (m_widgetHud)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_widgetHud))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateTimer(gameState->GetTimer());
		}
	}
}

void APlayerHUD::UpdateScore()
{
	if (m_widgetHud)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_widgetHud))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateScore(gameState->GetScore());
		}
	}
}
