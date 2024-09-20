#include "UI/Widget_HomeMenu.h"

#include "Components/Button.h"


void UWidget_HomeMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_startButton)
	{
		m_startButton->OnClicked.AddDynamic(this, &UWidget_HomeMenu::StartButtonOnClicked);
	}
}

void UWidget_HomeMenu::StartButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("I WAS CLICKED"));
}
