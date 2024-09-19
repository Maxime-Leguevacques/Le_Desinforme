#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HUD.generated.h"


UCLASS()
class LEDESINFORME_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateTimer(float _timer);
	void UpdateScore(int _score);
};
