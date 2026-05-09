// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAL2PlayerCharacter.h"

#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "Projectiles/TKAL2ProjectileMagic.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
ATKAL2PlayerCharacter::ATKAL2PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	MuzzleSocketName = "Muzzle_01";
}

void ATKAL2PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATKAL2PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATKAL2PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Look);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this,
		&ATKAL2PlayerCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Jump);
}

void ATKAL2PlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	//X Direction based off of Controller Rotation
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	
	//Y is right of X
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
	
}

void ATKAL2PlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ATKAL2PlayerCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	//Play casting effect and sound attached to hand
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget,
		true);
	UGameplayStatics::PlaySound2D(this, CastingSound); //2D cause its on the player
	
	//Set 0.2s timer to shoot when hand is in correct position
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ATKAL2PlayerCharacter::AttackTimerElapsed, 
		AttackDelayTime);
	
}

void ATKAL2PlayerCharacter::AttackTimerElapsed()
{
	//Get spawn info for the projectile
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);;
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//Spawn Projectile
	AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnInfo);
	MoveIgnoreActorAdd(NewProj); //Ignore character
}



