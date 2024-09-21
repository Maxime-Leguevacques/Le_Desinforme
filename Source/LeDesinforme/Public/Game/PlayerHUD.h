#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


UCLASS()
class LEDESINFORME_API APlayerHUD : public AHUD
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> m_widgetClass;
	UUserWidget* m_currentWidget = nullptr;

public:
	virtual void BeginPlay() override;
	
	void UpdateTimer();
	void UpdateScore();
	void ShowHud();
};
