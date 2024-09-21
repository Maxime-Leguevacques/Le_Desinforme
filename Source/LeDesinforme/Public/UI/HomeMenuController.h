#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeMenuController.generated.h"


UCLASS()
class LEDESINFORME_API AHomeMenuController : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> m_widgetClass;
	UUserWidget* m_homeMenuWidget = nullptr;
	
public:	
	AHomeMenuController();

protected:
	virtual void BeginPlay() override;
};
