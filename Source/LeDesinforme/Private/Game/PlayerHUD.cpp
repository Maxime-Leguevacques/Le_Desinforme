#include "Game/PlayerHUD.h"

#include "Game/LeDesinformeGameInstance.h"
#include "Game/LeDesinformeGameState.h"
#include "UI/Widget_HUD.h"


void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (m_widgetClass)
	{
		m_currentWidget = CreateWidget<UUserWidget>(GetWorld(), m_widgetClass);

		if (m_currentWidget)
		{
			m_currentWidget->AddToViewport();
		}

		// Update HUD in the BeginPlay since when a new round starts, map is reloaded and HUD is reloaded as well, setting score to 0
		if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
		{
			// // Set input mode in case we were in HomeMenu previously
			// FInputModeGameOnly inputMode;
			// playerController->SetInputMode(inputMode);
			// playerController->SetShowMouseCursor(false);
			
			if (APlayerHUD* hud = Cast<APlayerHUD>(playerController->GetHUD()))
			{
				hud->UpdateScore();
			}
		}
	}

	ShowHud();
}

void APlayerHUD::UpdateTimer()
{
	
	if (m_currentWidget)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_currentWidget))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateTimer(gameState->GetTimer());
		}
	}
}

void APlayerHUD::UpdateScore()
{
	if (m_currentWidget)
	{
		if (UWidget_HUD* widget = Cast<UWidget_HUD>(m_currentWidget))
		{
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			widget->UpdateScore(gameState->GetScore());
		}
	}
}

void APlayerHUD::ShowHud()
{
	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly inputMode;
	switch (gameInstance->GetGameState())
	{
	case EGameState::HomeMenu:
		m_currentWidget->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EGameState::Playing:
		playerController->SetInputMode(inputMode);
		playerController->SetShowMouseCursor(false);
		m_currentWidget->SetVisibility(ESlateVisibility::Visible);
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

// // Set input mode in case we were in HomeMenu previously
// FInputModeGameOnly inputMode;
// playerController->SetInputMode(inputMode);
// playerController->SetShowMouseCursor(false);
