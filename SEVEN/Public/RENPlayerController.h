#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RENPlayerController.generated.h"

class UInputMappingContext; // IMC ���� ���� ����
class UInputAction; // IA ���� ���� ����

UCLASS()
class SEVEN_API ARENPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ARENPlayerController();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;
};
