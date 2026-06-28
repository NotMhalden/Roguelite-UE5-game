// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_ChasePlayer.h"

USTTask_ChasePlayer::USTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = true;
}


EStateTreeRunStatus USTTask_ChasePlayer::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	return (RunStatus = EStateTreeRunStatus::Running);

}



EStateTreeRunStatus USTTask_ChasePlayer::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	return (RunStatus = EStateTreeRunStatus::Running);
}
