#include "UI/UIController.h"

#include "Blueprint/UserWidget.h"
#include "Game/LeDesinformeGameInstance.h"
#include "Game/LeDesinformeGameState.h"
#include "UI/Widget_HUD.h"


class ALeDesinformeGameState;

AUIController::AUIController()
{
	PrimaryActorTick.bCanEverTick = true;
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
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	gameState->SetUiController(this);
	// TODO : change since its on begin play
	switch (gameInstance->GetGameState()) {
	case HomeMenu:
		SetupHomeMenu();
		break;
	case Playing:
		SetupPlaying();
		ShowHUDWidget();
		break;
	case PauseMenu:
		break;
	case WinMenu:
		break;
	case GameOverMenu:
		break;
	case EndGameMenu:
		break;
	}
}

void AUIController::Tick(float _deltaSeconds)
{
	Super::Tick(_deltaSeconds);
	if (m_HUDWidgetInstance)
	{
		UWidget_HUD* hudWidget = Cast<UWidget_HUD>(m_HUDWidgetInstance);
		ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
		hudWidget->UpdateTimer(gameState->GetTimer());
	}
}

#pragma region Widgets
void AUIController::ShowHUDWidget()
{
	if (m_HUDWidgetClass && !m_HUDWidgetInstance)
	{
		m_HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), m_HUDWidgetClass);
		if (m_HUDWidgetInstance)
		{
			m_HUDWidgetInstance->AddToViewport();
		}
	}}

void AUIController::HideHUDWidget()
{
	if (m_HUDWidgetInstance && m_HUDWidgetInstance->IsInViewport())
	{
		m_HUDWidgetInstance->RemoveFromParent();
		m_HUDWidgetInstance = nullptr;
	}}

void AUIController::ShowInteractWidget()
{
	if (m_interactWidgetClass && !m_InteractWidgetInstance)
	{
		m_InteractWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), m_interactWidgetClass);
		if (m_InteractWidgetInstance)
		{
			m_InteractWidgetInstance->AddToViewport();
		}
	}
}

void AUIController::HideInteractWidget()
{
	if (m_InteractWidgetInstance && m_InteractWidgetInstance->IsInViewport())
	{
		m_InteractWidgetInstance->RemoveFromParent();
		m_InteractWidgetInstance = nullptr;
	}
}

void AUIController::UpdateScore()
{
	if (m_HUDWidgetInstance)
	{
		UWidget_HUD* hudWidget = Cast<UWidget_HUD>(m_HUDWidgetInstance);
		ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
		hudWidget->UpdateScore(gameState->GetScore());
	}
}
#pragma endregion Widgets
