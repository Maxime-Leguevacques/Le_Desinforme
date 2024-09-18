#include "Game/PlayerHUD.h"

#include "UI/HUD_PlayerInGame.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (m_widgetClass)
	{
		m_currentWidget = CreateWidget<UUserWidget>(GetWorld(), m_widgetClass);

		if (m_currentWidget)
		{
			m_currentWidget->AddToViewport();
		}
	}
}

void APlayerHUD::UpdateTimer(float _timer)
{
	if (m_currentWidget)
	{
		UHUD_PlayerInGame* widget = Cast<UHUD_PlayerInGame>(m_currentWidget);
		if (widget)
		{
			widget->UpdateTimer(_timer);
		}
	}
}

void APlayerHUD::UpdateScore(float _score)
{
	if (m_currentWidget)
	{
		UHUD_PlayerInGame* widget = Cast<UHUD_PlayerInGame>(m_currentWidget);
		if (widget)
		{
			widget->UpdateScore(_score);
		}
	}
}
