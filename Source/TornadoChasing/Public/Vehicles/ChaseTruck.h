#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChaseTruck.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;

/**
 * Lightweight physics-driven pickup prototype.
 * Assign a truck Static Mesh in a Blueprint derived from this class.
 */
UCLASS(Blueprintable)
class TORNADOCHASING_API AChaseTruck : public APawn
{
    GENERATED_BODY()

public:
    AChaseTruck();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Truck")
    TObjectPtr<UStaticMeshComponent> TruckBody;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> ChaseCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driving", meta = (ClampMin = "1000.0"))
    float EngineForce = 1800000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driving", meta = (ClampMin = "1000.0"))
    float SteeringTorque = 900000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driving", meta = (ClampMin = "100.0"))
    float MaximumSpeed = 5500.0f;

private:
    void SetThrottle(float Value);
    void SetSteering(float Value);

    float ThrottleInput = 0.0f;
    float SteeringInput = 0.0f;
};
