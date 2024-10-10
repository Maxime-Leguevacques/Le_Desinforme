#include "UI/Widget_HUD.h"

#include "Components/TextBlock.h"


void UWidget_HUD::UpdateTimer(float _timer)
{
	// Whole part of timer
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_textTimerWhole"))))
	{
		int wholeTimerPart = FMath::FloorToInt(_timer);
		if (wholeTimerPart >= 0)
		{
			FString stringTimer = FString::FromInt(wholeTimerPart);
			FText textTimerValue = FText::FromString(stringTimer);
			textTimer->SetText(textTimerValue);
		}
	}
	// Decimal part of timer
	if (UTextBlock* textTimer = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_textTimerDecimal"))))
	{
		float fractionalPart = _timer - FMath::FloorToFloat(_timer);
		int decimalPart = FMath::FloorToInt(fractionalPart * 10.f);
		FString stringTimer = FString::Printf(TEXT(".%d"), decimalPart);
		FText textTimerValue = FText::FromString(stringTimer);
		textTimer->SetText(textTimerValue);
	}
}

void UWidget_HUD::UpdateScore(int _score)
{
	if (UTextBlock* textScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("m_textScore"))))
	{
		FText textScoreValue = FText::AsNumber(_score);
		textScore->SetText(textScoreValue);
	}
}
