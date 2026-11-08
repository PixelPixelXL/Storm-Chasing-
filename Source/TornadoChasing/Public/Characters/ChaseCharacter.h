#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Starter character used to test first-person and third-person camera views.
 * Designed to be extended with Blueprint.
 */
UCLASS(Blueprintable)
class TORNADOCHASING_API AChaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AChaseCharacter();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> ThirdPersonCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

private:
    void ToggleCamera();

    bool bIsFirstPerson = false;
};
