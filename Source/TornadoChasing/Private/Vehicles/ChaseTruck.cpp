#include "Vehicles/ChaseTruck.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

AChaseTruck::AChaseTruck()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Disabled;

    TruckBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TruckBody"));
    SetRootComponent(TruckBody);
    TruckBody->SetSimulatePhysics(true);
    TruckBody->SetLinearDamping(0.35f);
    TruckBody->SetAngularDamping(2.5f);
    TruckBody->SetCollisionProfileName(TEXT("PhysicsActor"));

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(TruckBody);
    CameraBoom->TargetArmLength = 650.0f;
    CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 5.0f;

    ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
    ChaseCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    ChaseCamera->bUsePawnControlRotation = false;
}

void AChaseTruck::BeginPlay()
{
    Super::BeginPlay();

    // A Blueprint child should provide the visible truck mesh.
    if (TruckBody->GetStaticMesh())
    {
        TruckBody->SetSimulatePhysics(true);
    }
}

void AChaseTruck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (!PlayerInputComponent) return;

    PlayerInputComponent->BindAxis(TEXT("VehicleThrottle"), this, &AChaseTruck::SetThrottle);
    PlayerInputComponent->BindAxis(TEXT("VehicleSteering"), this, &AChaseTruck::SetSteering);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
}

void AChaseTruck::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!TruckBody->IsSimulatingPhysics()) return;

    const FVector Forward = TruckBody->GetForwardVector();
    const FVector Velocity = TruckBody->GetPhysicsLinearVelocity();
    const float ForwardSpeed = FVector::DotProduct(Velocity, Forward);
    const bool bBelowSpeedLimit = FMath::Abs(ForwardSpeed) < MaximumSpeed
        || FMath::Sign(ThrottleInput) != FMath::Sign(ForwardSpeed);

    if (!FMath::IsNearlyZero(ThrottleInput) && bBelowSpeedLimit)
    {
        TruckBody->AddForce(Forward * ThrottleInput * EngineForce);
    }

    if (!FMath::IsNearlyZero(SteeringInput) && !Velocity.IsNearlyZero(10.0f))
    {
        const float SpeedFactor = FMath::Clamp(Velocity.Size() / 1200.0f, 0.15f, 1.0f);
        TruckBody->AddTorqueInRadians(
            FVector::UpVector * SteeringInput * SteeringTorque * SpeedFactor);
    }
}

void AChaseTruck::SetThrottle(float Value)
{
    ThrottleInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AChaseTruck::SetSteering(float Value)
{
    SteeringInput = FMath::Clamp(Value, -1.0f, 1.0f);
}
