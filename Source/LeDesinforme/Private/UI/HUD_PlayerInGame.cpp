#include "UI/HUD_PlayerInGame.h"

#include "Components/TextBlock.h"


void UHUD_PlayerInGame::UpdateTimer(float _timer)
{
	// Whole part of timer
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Timer_Whole"))))
	{
		int wholeTimerPart = FMath::FloorToInt(_timer);
		FString stringTimer = FString::FromInt(wholeTimerPart);
		FText textTimerValue = FText::FromString(stringTimer);
		textTimer->SetText(textTimerValue);
	}
	// Decimal part of timer
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Timer_Decimal"))))
	{
		float fractionalPart = _timer - FMath::FloorToFloat(_timer);
		int decimalPart = FMath::FloorToInt(fractionalPart * 10.f);
		FString stringTimer = FString::Printf(TEXT(".%d"), decimalPart);
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
