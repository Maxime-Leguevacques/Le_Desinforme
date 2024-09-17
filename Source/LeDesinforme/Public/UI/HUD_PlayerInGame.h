#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_PlayerInGame.generated.h"


UCLASS()
class LEDESINFORME_API UHUD_PlayerInGame : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UCanvasPanel* m_canvasPanel;
	
protected:
	virtual void NativeConstruct() override;
};
