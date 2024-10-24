#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Employee.generated.h"


UCLASS()
class LEDESINFORME_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	AEmployee();

protected:
	virtual void BeginPlay() override;

	void SetupRandomSkin();

public:	
	virtual void Tick(float _deltaTime) override;
};
