#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


class UInputMappingContext;
class UInputAction;


UCLASS()
class LEDESINFORME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
#pragma region Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* m_inputMappingContext = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaLook;
#pragma endregion Input
	

protected:
	virtual void BeginPlay() override;

private:
#pragma region Input Action functions
	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
#pragma endregion Input Action functions
	
public:	
	virtual void Tick(float _deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;
};
