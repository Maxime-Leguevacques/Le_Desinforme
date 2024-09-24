#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIController.generated.h"


UCLASS()
class LEDESINFORME_API AUIController : public AActor
{
	GENERATED_BODY()

protected:
	// Selected widget class of homeMenu to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> m_homeMenuWidgetClass;
	// Instance of homeMenuWidgetClass
	UUserWidget* m_homeMenuWidgetInstance = nullptr;
		
public:	
	AUIController();

private:
	void SetupHomeMenuWidget();
	void SetupPlayingWidget();
	
protected:
	virtual void BeginPlay() override;
};
