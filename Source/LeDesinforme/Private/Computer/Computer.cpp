#include "Computer/Computer.h"

#include "Components/StaticMeshComponent.h"


AComputer::AComputer()
{
	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);
}

void AComputer::BeginPlay()
{
	Super::BeginPlay();
}
