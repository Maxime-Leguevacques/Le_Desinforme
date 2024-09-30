#include "UI/UIController.h"

#include "Blueprint/UserWidget.h"
#include "Game/LeDesinformeGameInstance.h"


AUIController::AUIController()
{
}

void AUIController::SetupHomeMenu()
{
	// Setup home menu widget
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
				inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				playerController->SetShowMouseCursor(true);
				playerController->SetInputMode(inputMode);
			}
		}
	}

	// Setup external camera
	if (APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (m_cameraHomeMenu)
		{
			playerController->SetViewTarget(m_cameraHomeMenu);
		}
	}
}

void AUIController::SetupPlaying()
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
	gameInstance->SetUiController(this);
	switch (gameInstance->GetGameState()) {
	case EGameState::HomeMenu:
		SetupHomeMenu();
		break;
	case EGameState::Playing:
		SetupPlaying();
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

void AUIController::AddCursorOnScreen()
{
	if (m_cursorWidgetClass && !m_cursorWidgetInstance)
	{
		m_cursorWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), m_cursorWidgetClass);
		if (m_cursorWidgetInstance)
		{
			m_cursorWidgetInstance->AddToViewport();
		}
	}
}

void AUIController::RemoveCursorFromScreen()
{
	if (m_cursorWidgetInstance && m_cursorWidgetInstance->IsInViewport())
	{
		m_cursorWidgetInstance->RemoveFromParent();
		m_cursorWidgetInstance = nullptr;
	}
}
