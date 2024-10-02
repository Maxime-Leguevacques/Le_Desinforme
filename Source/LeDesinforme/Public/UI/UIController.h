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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HomeMenuLevel")
	ACameraActor* m_cameraHomeMenu = nullptr;
	
#pragma region Widgets
	// Selected widget class of homeMenu to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HomeMenuLevel")
	TSubclassOf<UUserWidget> m_homeMenuWidgetClass;
	UUserWidget* m_homeMenuWidgetInstance = nullptr;
	// Selected widget class of the cursor to create when zooming on a valid object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	TSubclassOf<UUserWidget> m_interactWidgetClass;
	UUserWidget* m_InteractWidgetInstance = nullptr;
#pragma endregion Widgets
	
public:	
	AUIController();

private:
	void SetupHomeMenu();
	void SetupPlaying();
	
protected:
	virtual void BeginPlay() override;

public:
	void ShowPlayingWidget();
	void HidePlayingWidget();
	void ShowInteractWidget();
	void HideInteractWidget();
};
