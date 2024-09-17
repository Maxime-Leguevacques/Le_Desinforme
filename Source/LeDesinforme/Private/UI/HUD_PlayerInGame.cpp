#include "UI/HUD_PlayerInGame.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"


void UHUD_PlayerInGame::NativeConstruct()
{
	Super::NativeConstruct();

	if (!m_canvasPanel)
	{
		m_canvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("CanvasPanel"));

		if (m_canvasPanel)
		{
			WidgetTree->RootWidget = m_canvasPanel;
		}
	}
}
