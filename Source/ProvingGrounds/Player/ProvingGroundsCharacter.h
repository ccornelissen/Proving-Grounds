// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ProvingGroundsCharacter.generated.h"

class UInputComponent;
class AGun;

UCLASS(config = Game)
class PROVINGGROUNDS_API AProvingGroundsCharacter : public ACharacter
{
	GENERATED_BODY()

	//1P Pawn Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "First Person")
	class USkeletalMeshComponent* Mesh1P = nullptr;

	//1P camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "First Person", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

	//3P Pawn Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Third Person")
	class USkeletalMeshComponent* Mesh3P = nullptr;

	//Spring arm component (Camera boom) for 3rd person setting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Third Person", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ThirdPersonCameraArm = nullptr;

	//3rd person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Third Person", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCameraComponent = nullptr;

	bool bIsFirstPerson = true;

public:
	// Sets default values for this character's properties
	AProvingGroundsCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SwitchView();

	UFUNCTION(BlueprintCallable, Category = "Player")
	bool IsDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	float fPlayerMaxHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = Gameplay)
	float fPlayerCurrentHealth;

protected:
	//Player starting weapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AGun> StartingGunBP;
	
	AGun* StartingGun = nullptr;

	/** Fires a projectile. */
	void OnFire();

	/** Player Movement Functions */
	void MoveForward(float Val);

	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);


};
