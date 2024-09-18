#include "Game/PlayerHUD.h"


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
