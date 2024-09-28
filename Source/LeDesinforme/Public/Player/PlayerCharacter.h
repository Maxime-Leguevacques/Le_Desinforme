#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


class UInputMappingContext;
class UInputAction;


UENUM(BlueprintType)
enum class ECameraState : uint8
{
	Default		UMETA(DisplayName = "Default"),
	Focused		UMETA(DisplayName = "FocusedOnScreen")
};

UCLASS()
class LEDESINFORME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

private:
#pragma region Zoom Variables
	bool m_isZooming = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_defaultFov = 90.0f;
	float m_currentFov = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_zoomFov = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float m_zoomSpeed = 0.3f;
	float m_targetFov;
	float m_fovInterpolateSpeed = 0.0f;
#pragma endregion Zoom Variables
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_springArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_camera = nullptr;
	ECameraState m_cameraState;
	
protected:
#pragma region Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* m_inputMappingContext = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_iaLook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* m_zoom;
#pragma endregion Input


protected:
	virtual void BeginPlay() override;
	void PostInitializeComponents() override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;
	
private:
	void SetupCamera();
	void SetupFov();
	
#pragma region Input Action functions
	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
	void ZoomStart(const FInputActionValue& _value);
	void ZoomEnd(const FInputActionValue& _value);
#pragma endregion Input Action functions

	void UpdateFov(float _deltaTime);
};
