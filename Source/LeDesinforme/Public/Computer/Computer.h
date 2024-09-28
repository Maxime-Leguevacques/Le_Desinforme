#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Computer.generated.h"


UCLASS()
class LEDESINFORME_API AComputer : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_staticMeshComponent = nullptr;

public:	
	AComputer();

protected:
	virtual void BeginPlay() override;
};
