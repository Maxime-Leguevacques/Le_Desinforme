#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_PlayerInGame.generated.h"


UCLASS()
class LEDESINFORME_API UHUD_PlayerInGame : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateTimer(float _timer);
	void UpdateScore(int _score);
};
