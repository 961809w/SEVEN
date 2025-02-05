
#include "RENPlayerController.h"
#include "EnhancedInputSubsystems.h"

ARENPlayerController::ARENPlayerController()
    : InputMappingContext(nullptr),
	LookAction(nullptr), MoveAction(nullptr)

{
}


void ARENPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input Subsystem 등록
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);  // Input Mapping Context 적용
    }
}



