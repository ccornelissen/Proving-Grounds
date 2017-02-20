// Fill out your copyright notice in the Description page of Project Settings.

#include "ProvingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//Get the current waypoint the AI is on 
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//Get a reference to the controlled guard pawn
	APatrollingGuard* ControlledGuard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());

	//Update the waypoint to the current index number
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, ControlledGuard->PatrolPoints[Index]);

	//Iterate to the next waypoint number
	Index = (Index + 1) % ControlledGuard->PatrolPoints.Num();

	//Update the set waypoint
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}




