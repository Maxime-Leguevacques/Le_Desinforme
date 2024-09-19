#include "UI/HUD_PlayerInGame.h"

#include "Components/TextBlock.h"


void UHUD_PlayerInGame::UpdateTimer(float _timer)
{
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Timer"))))
	{
		FString stringTimer = FString::Printf(TEXT("%.1f"), _timer);
		FText textTimerValue = FText::FromString(stringTimer);
		textTimer->SetText(textTimerValue);
	}
}

void UHUD_PlayerInGame::UpdateScore(int _score)
{
	if (UTextBlock* textScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Score"))))
	{
		FText textScoreValue = FText::AsNumber(_score);
		textScore->SetText(textScoreValue);
	}
}
