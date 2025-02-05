#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "REN.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputComponent; // Ãß°¡

struct FInputActionValue;

UCLASS()
class SEVEN_API AREN : public APawn
{
    GENERATED_BODY()

public:
    AREN();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* Capsule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float NormalSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float LookSensitivity;

    UFUNCTION()
    void Move(const FInputActionValue& value);

    UFUNCTION()
    void Look(const FInputActionValue& value);

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
