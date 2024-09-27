#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "UIController.generated.h"


UCLASS()
class LEDESINFORME_API AUIController : public AActor
{
	GENERATED_BODY()

protected:
	// Selected widget class of homeMenu to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HomeMenuLevel")
	TSubclassOf<UUserWidget> m_homeMenuWidgetClass;
	// Instance of homeMenuWidgetClass
	UUserWidget* m_homeMenuWidgetInstance = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HomeMenuLevel")
	ACameraActor* m_cameraHomeMenu = nullptr;
		
public:	
	AUIController();

private:
	void SetupHomeMenu();
	void SetupPlaying();
	
protected:
	virtual void BeginPlay() override;
};
