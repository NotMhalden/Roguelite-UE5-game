// Fill out your copyright notice in the Description page of Project Settings.


#include "STEvaluator_RunEQSQuery.h"

#include "StateTreeExecutionContext.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "StateTreeAsyncExecutionContext.h"
#include "Roguelite/HexGameplayTags.h"

void FSTEvaluator_RunEQSQuery::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FEQSEvaluatorData& Data = Context.GetInstanceData(*this);
	
	if (Data.bInFlight)
		return;
	
	
	const bool bEventPending = Context.HasEventToProcess(TAG_Encounter_PlayerReposition.GetTag());
	const bool bFirstRun = not Data.bHasQueried;
	if (bFirstRun or bEventPending)
	{
		Data.bHasQueried = true;
		
		FEnvQueryRequest Request(Data.EnvironmentQuery, Data.Owner);
		Request.SetFloatParam(FName("Donut.InnerRadius"), Data.InnerRadius);
		Request.SetFloatParam(FName("Donut.OuterRadius"), Data.OuterRadius);
		
		Data.bInFlight = true;
		Request.Execute(Data.EQRunMode, FQueryFinishedSignature::CreateLambda(
			[WeakContext = Context.MakeWeakExecutionContext()]
			(TSharedPtr<FEnvQueryResult> Result) mutable
			{
				FStateTreeStrongExecutionContext StrongContext = WeakContext.MakeStrongExecutionContext();
				
				if (FInstanceDataType* D = StrongContext.GetInstanceDataPtr<FInstanceDataType>())
				{
					D -> bInFlight = false;
					if (Result and Result -> IsSuccessful())
						D -> OutputLocation = Result->GetItemAsLocation(0); 
				}
			}
		));
	}
}
