// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAL2PlayerCharacter.h"

#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "Projectiles/TKAL2ProjectileMagic.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"   
#include "../../../Intermediate/ProjectFiles/TKAL2GameTypes.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ActionSystem/TKAL2ActionSystemComponent.h"

TAutoConsoleVariable<float> CVarProjectileAdjustmentDebugDrawing(TEXT("game.projectile.DebugDraw"), 0.0f,
	TEXT("Enable projectile aim adjustment debug rendering (0 = off, < 0 is duration"), ECVF_Cheat);


// Sets default values
ATKAL2PlayerCharacter::ATKAL2PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	ActionSystemComp = CreateDefaultSubobject<UTKAL2ActionSystemComponent>(TEXT("ActionSystemComp"));
	
	MuzzleSocketName = "Muzzle_01";
}

void ATKAL2PlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ActionSystemComp->OnHealthChanged.AddDynamic(this, &ATKAL2PlayerCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void ATKAL2PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ATKAL2PlayerCharacter::Jump);
		
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this,
		&ATKAL2PlayerCharacter::StartProjectileAttack, PrimaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, 
		&ATKAL2PlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, 
		&ATKAL2PlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass);

	                                                                                                                                                                                                                                                                                                                                               
}

float ATKAL2PlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComp->ApplyHealthChange(-DamageAmount);
	
	return ActualDamage;
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

void ATKAL2PlayerCharacter::StartProjectileAttack(TSubclassOf<ATKAL2Projectile> ProjClass)
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
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ATKAL2PlayerCharacter::AttackTimerElapsed, ProjClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, 
		false);
	
}

void ATKAL2PlayerCharacter::AttackTimerElapsed(TSubclassOf<ATKAL2Projectile> ProjClass)
{
	//Get spawn info for the projectile
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FVector EyeLocation = CameraComp->GetComponentLocation();
	FRotator EyeRotation = GetControlRotation();
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	UWorld* World = GetWorld();
	FHitResult Hit;
	FVector AdjustedTargetLocation;
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, QueryParams))
	{
		AdjustedTargetLocation = Hit.Location;
	} else
	{
		AdjustedTargetLocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();
	
	//Spawn Projectile
	AActor* NewProj = World->SpawnActor<AActor>(ProjClass, SpawnLocation, SpawnRotation, SpawnInfo);
	MoveIgnoreActorAdd(NewProj); //Ignore character
	
	float DebugDrawDuration = CVarProjectileAdjustmentDebugDrawing.GetValueOnGameThread();
	
#if !UE_BUILD_SHIPPING
	if (DebugDrawDuration > 0.0f)
	{
		// hit location or trace end
		DrawDebugBox(World, AdjustedTargetLocation, FVector(20.0f), FColor::Green,false, 
			DebugDrawDuration);
	
		//adjusted line trace
		DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugDrawDuration);
	
		//new proj path
		DrawDebugLine(World, SpawnLocation, AdjustedTargetLocation, FColor::Yellow, false,
			DebugDrawDuration);
		//orig path
		DrawDebugLine(World, SpawnLocation, SpawnLocation + (GetControlRotation().Vector() * 5000.0f), 
			FColor::Purple, false, DebugDrawDuration);
	}
#endif
	
}

void ATKAL2PlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);
		
		GetMovementComponent()->StopMovementImmediately();
		
		PlayAnimMontage(DeathMontage);
	}
}



