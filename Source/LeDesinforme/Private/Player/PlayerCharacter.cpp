#include "Player/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Computer/Computer.h"
#include "Game/LeDesinformeGameState.h"
#include "GameFramework/CharacterMovementComponent.h"


// The height of the employee's computer screen to set the player camera to when focused
const float EMPLOYEE_COMPUTER_SCREEN_HEIGHT = 179.0f;
const float OFFSET_FROM_COMPUTER_SCREEN = 75.0f;


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetupSpringArm();
	SetupCamera();
	SetupFov();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* playerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	subsystem->AddMappingContext(m_inputMappingContext, 0);

	if (m_camera)
	{
		m_camera->SetFieldOfView(m_currentFov);
	}
}

void APlayerCharacter::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (m_camera)
	{
		switch (m_cameraState) {
		case Default:
			break;
		case Zooming:
			DetectObjects();
			break;
		default:
			break;
		}
		
		UpdateFov(_deltaTime);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

	// Bind Input Actions to functions
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(_playerInputComponent))
	{
		enhancedInputComponent->BindAction(m_iaMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInputComponent->BindAction(m_iaLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhancedInputComponent->BindAction(m_iaZoom, ETriggerEvent::Started, this, &APlayerCharacter::ZoomStart);
		enhancedInputComponent->BindAction(m_iaZoom, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomEnd);
		enhancedInputComponent->BindAction(m_iaInteract, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		enhancedInputComponent->BindAction(m_iaExit, ETriggerEvent::Triggered, this, &APlayerCharacter::Exit);
	}
}

void APlayerCharacter::SetupSpringArm()
{
	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_springArm->SetupAttachment(RootComponent);
	m_springArm->TargetArmLength = 0.0f;
	m_springArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	m_springArm->bUsePawnControlRotation = true;
}

void APlayerCharacter::SetupCamera()
{
	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_camera->SetupAttachment(m_springArm, USpringArmComponent::SocketName);
	m_camera->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	// Lock the camera to the character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// Only the spring arm rotates
	m_camera->bUsePawnControlRotation = false;
	// Set the character rotation to the direction of the movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	m_cameraState = Default;
}

void APlayerCharacter::SetupFov()
{
	m_currentFov = m_defaultFov;
	m_targetFov = m_defaultFov;
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
	if (m_cameraState == Default || m_cameraState == Zooming)
	{
		FVector2D lookVector = _value.Get<FVector2D>();
		if (IsValid(Controller))
		{
			AddControllerYawInput(lookVector.X);
			AddControllerPitchInput(lookVector.Y);
		}
	}
}

void APlayerCharacter::ZoomStart(const FInputActionValue& _value)
{

	m_cameraState = Zooming;
	// TODO : Check if m_isZooming is usefull
	m_isZooming = true;
	m_targetFov = m_zoomFov;
	m_fovInterpolateSpeed = FMath::Abs(m_currentFov - m_targetFov) * m_zoomSpeed;
}

void APlayerCharacter::ZoomEnd(const FInputActionValue& _value)
{
	m_cameraState = Default;
	m_isZooming = false;
	m_targetFov = m_defaultFov;
	m_fovInterpolateSpeed = FMath::Abs(m_currentFov - m_targetFov) * m_zoomSpeed;
	
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	gameState->GetUiController()->HideInteractWidget();
	
}

void APlayerCharacter::Interact(const FInputActionValue& _value)
{
	if (m_focusedComputer)
	{
		m_cameraState = Focused;
		FocusOnComputer();
	}
}

void APlayerCharacter::Exit(const FInputActionValue& _value)
{
	m_cameraState = Default;
	// Hide UI
	// Switch camera to player camera
	APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	playerController->SetViewTarget(this);
	// Enable player movement
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
	gameState->GetUiController()->ShowHUDWidget();
}
#pragma endregion Input Action functions

void APlayerCharacter::UpdateFov(const float _deltaTime)
{
	m_currentFov = FMath::FInterpTo(m_currentFov, m_targetFov, _deltaTime, m_fovInterpolateSpeed);
	m_camera->SetFieldOfView(m_currentFov);
}

void APlayerCharacter::DetectObjects()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (!playerController)
	{
		return;
	}

	// Get camera location and rotation
	FVector cameraLocation;
	FRotator cameraRotation;
	playerController->GetPlayerViewPoint(cameraLocation, cameraRotation);
	// Create a start and end point for the raycast where object detection will occur
	FVector raycastEnd = cameraLocation + (cameraRotation.Vector() * 500.0f);
	// Setup raycast
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	// If object is detected
	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, cameraLocation, raycastEnd, ECC_Visibility, collisionParams))		// cameraLocation is used as the raycast start point
	{
		AComputer* detectedComputer = Cast<AComputer>(hitResult.GetActor());
		if(IsValid(detectedComputer))
		{
			m_focusedComputer = detectedComputer;
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			gameState->GetUiController()->ShowInteractWidget();
		}
		else
		{
			m_focusedComputer = nullptr;
			ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
			gameState->GetUiController()->HideInteractWidget();
		}
	}
	else
	{
		m_focusedComputer = nullptr;
		ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
		gameState->GetUiController()->HideInteractWidget();
	}
}

void APlayerCharacter::FocusOnComputer()
{
	// Create a camera facing the computer
	FRotator cameraRotation = m_focusedComputer-> GetActorForwardVector().Rotation() + FRotator(0.0f, -90.0f, 0.0f);
	FVector offset = FVector(0.0f, OFFSET_FROM_COMPUTER_SCREEN, 0.0f);
	FVector rotatedOffset = m_focusedComputer-> GetActorForwardVector().Rotation().RotateVector(offset);
	FVector cameraLocation = m_focusedComputer->GetActorLocation() + rotatedOffset;
	cameraLocation.Z = EMPLOYEE_COMPUTER_SCREEN_HEIGHT;
	// Camera looking at the computer's screen
	if (ACameraActor* newCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), cameraLocation, cameraRotation))
	{
		// Disable player movement and rotation
		APlayerController* playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		playerController->SetViewTarget(newCamera);
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		// Hide the HUD widget
		ALeDesinformeGameState* gameState = Cast<ALeDesinformeGameState>(GetWorld()->GetGameState());
		gameState->GetUiController()->HideHUDWidget();
	}
}

