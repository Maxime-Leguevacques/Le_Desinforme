#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HomeMenu.generated.h"


UCLASS()
class LEDESINFORME_API UWidget_HomeMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* m_startButton;

private:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void StartButtonOnClicked();
};
