#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Starter character for the storm-chasing prototype.
 * Supports basic on-foot movement and first-/third-person camera views.
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
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void ToggleCamera();

    bool bIsFirstPerson = false;
};
