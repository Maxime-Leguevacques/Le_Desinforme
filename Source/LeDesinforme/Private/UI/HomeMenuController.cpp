#include "UI/HomeMenuController.h"

#include "Blueprint/UserWidget.h"


AHomeMenuController::AHomeMenuController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHomeMenuController::BeginPlay()
{
	Super::BeginPlay();

	m_homeMenuWidget = CreateWidget<UUserWidget>(GetWorld(), m_widgetClass);

	if (m_homeMenuWidget)
	{
		m_homeMenuWidget->AddToViewport();

		if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
		{
			FInputModeUIOnly inputMode;
			inputMode.SetWidgetToFocus(m_homeMenuWidget->TakeWidget());
			inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			playerController->SetInputMode(inputMode);
			playerController->SetShowMouseCursor(true);
		}
	}
}