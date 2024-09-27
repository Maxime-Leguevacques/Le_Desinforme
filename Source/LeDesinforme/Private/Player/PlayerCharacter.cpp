#include "Player/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	subsystem->AddMappingContext(m_inputMappingContext, 0);

}

#pragma region Input Action functions
void APlayerCharacter::Move(const FInputActionValue& _value)
{
	FVector2D direction = _value.Get<FVector2D>();
	if (IsValid(Controller))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);
		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(forwardDirection, direction.Y);
		AddMovementInput(rightDirection, direction.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& _value)
{
	FVector2D lookVector = _value.Get<FVector2D>();
	if (IsValid(Controller))
	{
		AddControllerYawInput(lookVector.X);
		AddControllerPitchInput(lookVector.Y);
	}
}
#pragma endregion Input Action functions

void APlayerCharacter::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

	// Bind Input Actions to functions
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(_playerInputComponent))
	{
		enhancedInputComponent->BindAction(m_iaMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(m_iaLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}

