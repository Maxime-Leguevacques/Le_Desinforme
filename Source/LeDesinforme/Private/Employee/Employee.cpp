#include "Employee/Employee.h"


AEmployee::AEmployee()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEmployee::BeginPlay()
{
	Super::BeginPlay();

	SetupRandomSkin();
}

void AEmployee::SetupRandomSkin()
{
	// Get all skeletal meshes
	// Select one at random
	// Add its material
	// Set its skin enum
}

void AEmployee::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}
