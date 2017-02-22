// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROVINGGROUNDS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditInstanceOnly, Category = "Patrol Points")
		TArray<AActor*> PatrolPoints;

	// Sets default values for this component's properties
	UPatrolRouteComponent();

		
	
};
