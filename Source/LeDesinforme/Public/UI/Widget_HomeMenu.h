#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HomeMenu.generated.h"


UCLASS()
class LEDESINFORME_API UWidget_HomeMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* m_startButton = nullptr;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartButtonClicked();
};
