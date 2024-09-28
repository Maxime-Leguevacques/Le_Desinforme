#pragma once

#include "CoreMinimal.h"
#include "DeskLocationActor.h"
#include "Computer/Computer.h"
#include "EmployeeComputer.generated.h"


UCLASS()
class LEDESINFORME_API AEmployeeComputer : public AComputer
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Employee", meta = (AllowPrivateAccess = "true"))
	ADeskLocationActor* m_deskLocationActor = nullptr;

public:
	ADeskLocationActor* GetDeskLocationActor();
};
