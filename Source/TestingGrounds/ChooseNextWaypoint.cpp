// Copyright By Matias Fuentes @ Elder Branch 2017

#include "ChooseNextWaypoint.h"
#include "PatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	UPatrollingComponent* PatrollingComponent = AIActor->FindComponentByClass<UPatrollingComponent>();

	if(PatrollingComponent && BlackboardComponent)
	{
		UChooseNextWaypoint::SetNextWaypoint(BlackboardComponent, PatrollingComponent);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UChooseNextWaypoint::SetNextWaypoint(UBlackboardComponent* BlackboardComponent, UPatrollingComponent* PatrollingComponent)
{
	if(PatrollingComponent->PatrollingPoints.Num() > 0)
	{
		int32 WaypointIndex = BlackboardComponent->GetValueAsInt(UChooseNextWaypoint::NextWaypointIndex.SelectedKeyName);
		UObject* NextWaypoint = PatrollingComponent->PatrollingPoints[WaypointIndex];

		BlackboardComponent->SetValueAsObject(UChooseNextWaypoint::NextWaypoint.SelectedKeyName, NextWaypoint);
		UChooseNextWaypoint::SetNextWaypointIndex(BlackboardComponent, PatrollingComponent, WaypointIndex);
	}
}

void UChooseNextWaypoint::SetNextWaypointIndex(UBlackboardComponent* BlackboardComponent, UPatrollingComponent* PatrollingComponent, int32 WaypointIndex)
{
	if(PatrollingComponent->PatrollingPoints.Num() - 1 > WaypointIndex)
	{
		int32 NextWaypointIndex = WaypointIndex + 1;
		BlackboardComponent->SetValueAsInt(UChooseNextWaypoint::NextWaypointIndex.SelectedKeyName, NextWaypointIndex);
	}
	else BlackboardComponent->SetValueAsInt(UChooseNextWaypoint::NextWaypointIndex.SelectedKeyName, 0);
}