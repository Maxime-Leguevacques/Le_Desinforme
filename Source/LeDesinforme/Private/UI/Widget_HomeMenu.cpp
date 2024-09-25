#include "UI/Widget_HomeMenu.h"

#include "Components/Button.h"
#include "Game/LeDesinformeGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"


void UWidget_HomeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind buttons
	if (m_startButton)
	{
		m_startButton->OnClicked.AddDynamic(this, &UWidget_HomeMenu::OnStartButtonClicked);
	}
	if (m_quitButton)
	{
		m_quitButton->OnClicked.AddDynamic(this, &UWidget_HomeMenu::OnQuitButtonClicked);
	}
}

void UWidget_HomeMenu::OnStartButtonClicked()
{
	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	gameInstance->SetGameState(EGameState::Playing);
}

void UWidget_HomeMenu::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
