#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Computer.generated.h"


UCLASS()
class LEDESINFORME_API AComputer : public AActor
{
	GENERATED_BODY()

public:	
	AComputer();

protected:
	virtual void BeginPlay() override;

public:	
};
