#include "UI/UIController.h"

#include "Blueprint/UserWidget.h"
#include "Game/LeDesinformeGameInstance.h"


AUIController::AUIController()
{
}

void AUIController::SetupHomeMenuWidget()
{
	if (m_homeMenuWidgetClass)
	{
		m_homeMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), m_homeMenuWidgetClass);
		
		if (m_homeMenuWidgetInstance)
		{
			m_homeMenuWidgetInstance->AddToViewport();

			// Set InputMode
			if (APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
			{
				FInputModeUIOnly inputMode;
				// inputMode.SetWidgetToFocus(m_homeMenuWidgetInstance->TakeWidget());
				inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				playerController->SetShowMouseCursor(true);
				playerController->SetInputMode(inputMode);
			}
		}
	}
}

void AUIController::SetupPlayingWidget()
{
	// Set InputMode
	if (APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		FInputModeGameOnly inputMode;
		playerController->SetShowMouseCursor(false);
		playerController->SetInputMode(inputMode);
	}
}

void AUIController::BeginPlay()
{
	Super::BeginPlay();

	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	switch (gameInstance->GetGameState()) {
	case EGameState::HomeMenu:
		SetupHomeMenuWidget();
		break;
	case EGameState::Playing:
		SetupPlayingWidget();
		break;
	case EGameState::PauseMenu:
		break;
	case EGameState::WinMenu:
		break;
	case EGameState::GameOverMenu:
		break;
	case EGameState::EndGameMenu:
		break;
	}
}
