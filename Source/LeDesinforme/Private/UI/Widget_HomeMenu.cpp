#include "UI/Widget_HomeMenu.h"

#include "Components/Button.h"
#include "Game/LeDesinformeGameInstance.h"


void UWidget_HomeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_startButton)
	{
		m_startButton->OnClicked.AddDynamic(this, &UWidget_HomeMenu::OnStartButtonClicked);
	}
}

void UWidget_HomeMenu::OnStartButtonClicked()
{
	ULeDesinformeGameInstance* gameInstance = Cast<ULeDesinformeGameInstance>(GetGameInstance());
	gameInstance->SetGameState(EGameState::Playing);
}
