// Fill out your copyright notice in the Description page of Project Settings.

#include "ProvingGrounds.h"
#include "ProvingGroundsCharacter.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Weapons/Gun.h"

// Sets default values
AProvingGroundsCharacter::AProvingGroundsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	//THIRD PERSON COMPONENT SET UP
	Mesh3P = GetMesh();
	Mesh3P->SetOwnerNoSee(true); //Defaults to first person

	ThirdPersonCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonCameraArm"));
	ThirdPersonCameraArm->SetupAttachment(GetCapsuleComponent());

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(ThirdPersonCameraArm);

	//FIRST PERSON COMPONENT SET UP
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AProvingGroundsCharacter::BeginPlay()
{
	Super::BeginPlay();

	fPlayerCurrentHealth = fPlayerMaxHealth;

	ThirdPersonCameraComponent->SetActive(false); //Defaults to first person camera

	//Spawn the players starting gun
	UWorld* const World = GetWorld();

	if (StartingGunBP != nullptr && World != nullptr)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		StartingGun = World->SpawnActor<AGun>(StartingGunBP, SpawnLocation, SpawnRotation);
		StartingGun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		StartingGun->AnimInstance = Mesh1P->GetAnimInstance();
		StartingGun->FireAnimation = FireAnimation;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player missing a starting weapon!"));
	}
	
}

// Called every frame
void AProvingGroundsCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

// Called to bind functionality to input
void AProvingGroundsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AProvingGroundsCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProvingGroundsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProvingGroundsCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProvingGroundsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProvingGroundsCharacter::LookUpAtRate);
}

void AProvingGroundsCharacter::SwitchView()
{
	if (bIsFirstPerson)
	{
		Mesh1P->SetOwnerNoSee(true);
		FirstPersonCameraComponent->SetActive(false);

		Mesh3P->SetOwnerNoSee(false);
		ThirdPersonCameraComponent->SetActive(true);

		bIsFirstPerson = false;
	}
	else
	{
		Mesh1P->SetOwnerNoSee(false);
		FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
		FirstPersonCameraComponent->SetActive(true);;

		Mesh3P->SetOwnerNoSee(true);
		ThirdPersonCameraComponent->SetActive(false);

		bIsFirstPerson = true;
	}
}

bool AProvingGroundsCharacter::IsDead()
{
	if (fPlayerCurrentHealth <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AProvingGroundsCharacter::OnFire()
{
	if (StartingGun != nullptr)
	{
		StartingGun->OnFire();
	}
}

void AProvingGroundsCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProvingGroundsCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProvingGroundsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProvingGroundsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

