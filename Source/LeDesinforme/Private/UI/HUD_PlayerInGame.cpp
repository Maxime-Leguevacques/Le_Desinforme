#include "UI/HUD_PlayerInGame.h"

#include "Components/TextBlock.h"


void UHUD_PlayerInGame::UpdateTimer(float _timer)
{
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Timer"))))
	{
		FText textTimerValue = FText::AsNumber(_timer);
		textTimer->SetText(textTimerValue);
	}
}

void UHUD_PlayerInGame::UpdateScore(int _score)
{
	if (UTextBlock* textScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Timer"))))
	{
		FText textScoreValue = FText::AsNumber(_score);
		textScore->SetText(textScoreValue);
	}
}
