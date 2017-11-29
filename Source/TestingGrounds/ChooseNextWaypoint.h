// Copyright By Matias Fuentes @ Elder Branch 2017

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

class UPatrollingComponent;
/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector NextWaypointIndex;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector NextWaypoint;

private:
	void SetNextWaypoint(UBlackboardComponent* BlackboardComponent, UPatrollingComponent* PatrollingComponent);
	void SetNextWaypointIndex(UBlackboardComponent* BlackboardComponent, UPatrollingComponent* PatrollingComponent, int32 WaypointIndex);
};
