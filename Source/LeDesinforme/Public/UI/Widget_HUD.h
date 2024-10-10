#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD.generated.h"


UCLASS()
class LEDESINFORME_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* m_textTimerWhole = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* m_textTimerDecimal = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* m_textScore = nullptr;

public:
	void UpdateTimer(float _timer);
	void UpdateScore(int _score);
};
