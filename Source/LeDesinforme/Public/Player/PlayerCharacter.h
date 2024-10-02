#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


class UInputMappingContext;
class UInputAction;


UENUM(BlueprintType)
enum ECameraState
{
	// TODO : Check if Zooming can be a cameraState
	Default		UMETA(DisplayName = "Default"),
	Zooming		UMETA(DisplayName = "Zooming"),
	Focused		UMETA(DisplayName = "FocusedOnScreen")
};

UCLASS()
class LEDESINFORME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
#pragma region Zoom Variables
	bool m_isZooming = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_defaultFov = 90.0f;
	float m_currentFov;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_zoomFov = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_zoomSpeed = 0.3f;
	float m_targetFov;
	float m_fovInterpolateSpeed = 0.0f;
#pragma endregion Zoom Variables
		
#pragma region Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* m_inputMappingContext = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaLook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaInteract;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaExit;
#pragma endregion Input

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm")
	class USpringArmComponent* m_springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* m_camera;
	TEnumAsByte<ECameraState> m_cameraState;

	class AComputer* m_focusedComputer = nullptr;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;
	
private:
	void SetupSpringArm();
	void SetupCamera();
	void SetupFov();
	
#pragma region Input Action functions
	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
	void ZoomStart(const FInputActionValue& _value);
	void ZoomEnd(const FInputActionValue& _value);
	void Interact(const FInputActionValue& _value);
	void Exit(const FInputActionValue& _value);
#pragma endregion Input Action functions

	void UpdateFov(float _deltaTime);
	// When zooming, detect objects in view
	void DetectObjects();
	// Focus on a computer screen
	void FocusOnComputer();
};
