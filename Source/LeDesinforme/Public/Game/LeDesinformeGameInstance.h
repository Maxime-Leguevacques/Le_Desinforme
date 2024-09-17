#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LeDesinformeGameInstance.generated.h"


UCLASS()
class LEDESINFORME_API ULeDesinformeGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	int m_score = 0;
	
public:
	ULeDesinformeGameInstance();

public:
	virtual void Init() override;

	int GetScore() const;
	
	void SetScore(const int _score);
};
