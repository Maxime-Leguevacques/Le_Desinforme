#include "Player/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupCamera();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	subsystem->AddMappingContext(m_inputMappingContext, 0);

	SetupFov();
	if (m_camera)
		UE_LOG(LogTemp, Warning, TEXT("I AM HERE"));
	m_camera->SetFieldOfView(m_currentFov);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayerCharacter::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (m_camera)
	{
		UpdateFov(_deltaTime);
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Green, FString::Printf(TEXT("zooming : %d"),  m_isZooming));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

	// Bind Input Actions to functions
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(_playerInputComponent))
	{
		enhancedInputComponent->BindAction(m_iaMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(m_iaLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhancedInputComponent->BindAction(m_zoom, ETriggerEvent::Started, this, &APlayerCharacter::ZoomStart);
		enhancedInputComponent->BindAction(m_zoom, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomEnd);
	}
}

void APlayerCharacter::SetupCamera()
{
	// Setup Spring Arm
	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_springArm->SetupAttachment(RootComponent);
	m_springArm->TargetArmLength = 0.0f;
	m_springArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	// Setup Camera
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_camera->SetupAttachment(m_springArm, USpringArmComponent::SocketName);
	m_camera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	// Lock the camera to the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// Only the spring arm rotates
	m_springArm->bUsePawnControlRotation = true;
	m_camera->bUsePawnControlRotation = false;
	// Set the character rotation to the direction of the movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	m_cameraState = ECameraState::Default;
}

void APlayerCharacter::SetupFov()
{
	m_currentFov = m_defaultFov;
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

void APlayerCharacter::ZoomStart(const FInputActionValue& _value)
{
	m_isZooming = true;
	m_targetFov = m_zoomFov;
	m_fovInterpolateSpeed = FMath::Abs(m_currentFov - m_targetFov) * m_zoomSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Camera here"));
}

void APlayerCharacter::ZoomEnd(const FInputActionValue& _value)
{
	m_isZooming = false;
	m_targetFov = m_defaultFov;
	m_fovInterpolateSpeed = FMath::Abs(m_currentFov - m_targetFov) * m_zoomSpeed;
}  
#pragma endregion Input Action functions

void APlayerCharacter::UpdateFov(const float _deltaTime)
{
	m_currentFov = FMath::FInterpTo(m_currentFov, m_targetFov, _deltaTime, m_fovInterpolateSpeed);
	m_camera->SetFieldOfView(m_currentFov);
	if (m_camera)
		UE_LOG(LogTemp, Warning, TEXT("Current FOV: %f, Target FOV: %f"), m_currentFov, m_targetFov);

}

