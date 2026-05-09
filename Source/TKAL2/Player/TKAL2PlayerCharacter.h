// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TKAL2PlayerCharacter.generated.h"

class UTKAL2ActionSystemComponent;
class UTKAL2InteractionComponent;
class ATKAL2Projectile;
class UNiagaraSystem;
class ATKAL2ProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class TKAL2_API ATKAL2PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATKAL2PlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category="PrimaryAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ATKAL2Projectile> PrimaryAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ATKAL2Projectile> SecondaryAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ATKAL2Projectile> SpecialAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Death")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UTKAL2ActionSystemComponent> ActionSystemComp;
	
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void StartProjectileAttack(TSubclassOf<ATKAL2Projectile> ProjClass);
	
	void AttackTimerElapsed(TSubclassOf<ATKAL2Projectile> ProjClass);
	
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);
	
public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void PostInitializeComponents() override;
};
