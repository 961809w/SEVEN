#include "REN.h"
#include "EnhancedInputComponent.h"
#include "RENPlayerController.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h" // Ãß°¡

AREN::AREN()
{
    PrimaryActorTick.bCanEverTick = true;

    USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    Capsule->SetupAttachment(RootComponent);
    Capsule->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
    Capsule->SetSimulatePhysics(false);

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Capsule);
    SpringArm->TargetArmLength = 200.f;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    NormalSpeed = 600.0f;
    LookSensitivity = 2.0f;
}

void AREN::BeginPlay()
{
    Super::BeginPlay();
}

void AREN::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AREN::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ARENPlayerController* PlayerController = Cast<ARENPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AREN::Move
                );
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AREN::Look
                );
            }
        }
    }
}

void AREN::Move(const FInputActionValue& value)
{
    if (!Controller) return;

    const FVector2D MoveInput = value.Get<FVector2D>();
    FVector MoveDirection = (GetActorForwardVector() * MoveInput.X) + (GetActorRightVector() * MoveInput.Y);
    MoveDirection = MoveDirection.GetClampedToMaxSize(1.0f);

    AddActorLocalOffset(MoveDirection * NormalSpeed * GetWorld()->GetDeltaSeconds(), true);
}

void AREN::Look(const FInputActionValue& value)
{
    if (!Controller) return;

    FVector2D LookInput = value.Get<FVector2D>();

    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += LookInput.X * LookSensitivity;
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + (LookInput.Y * LookSensitivity), -89.0f, 89.0f);
    
    SetActorRotation(FRotator(NewRotation.Pitch, NewRotation.Yaw, 0.0f));
}
