#include "Characters/ChaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

AChaseCharacter::AChaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->JumpZVelocity = 420.0f;
    GetCharacterMovement()->AirControl = 0.25f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 350.0f;
    CameraBoom->bUsePawnControlRotation = true;

    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
    ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    ThirdPersonCamera->bUsePawnControlRotation = false;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(RootComponent);
    FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;
    FirstPersonCamera->SetActive(false);
}

void AChaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (!PlayerInputComponent)
    {
        return;
    }

    PlayerInputComponent->BindAxis("MoveForward", this, &AChaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AChaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AChaseCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AChaseCharacter::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("ToggleCamera", IE_Pressed, this, &AChaseCharacter::ToggleCamera);
}

void AChaseCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator ControlRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        AddMovementInput(FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X), Value);
    }
}

void AChaseCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator ControlRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        AddMovementInput(FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y), Value);
    }
}

void AChaseCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AChaseCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void AChaseCharacter::ToggleCamera()
{
    bIsFirstPerson = !bIsFirstPerson;

    FirstPersonCamera->SetActive(bIsFirstPerson);
    ThirdPersonCamera->SetActive(!bIsFirstPerson);
}
