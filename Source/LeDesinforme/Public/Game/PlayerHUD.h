#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


UCLASS()
class LEDESINFORME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// Selected widget class to create
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> m_widgetHudClass;
	UUserWidget* m_widgetHudInstance = nullptr;

public:
	virtual void BeginPlay() override;
	void DrawHUD() override;

	void UpdateTimer();
	void UpdateScore();
};
