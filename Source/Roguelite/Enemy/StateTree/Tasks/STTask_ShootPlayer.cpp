// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_ShootPlayer.h"

USTTask_ShootPlayer::USTTask_ShootPlayer(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = false;
}



EStateTreeRunStatus USTTask_ShootPlayer::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	return RunStatus = EStateTreeRunStatus::Failed;
}



EStateTreeRunStatus USTTask_ShootPlayer::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	return RunStatus = EStateTreeRunStatus::Failed;
}