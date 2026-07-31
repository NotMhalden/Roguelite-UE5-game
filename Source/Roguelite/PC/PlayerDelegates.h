// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerHealthChangeDelegate, int, /* CurrentPlayerHealth */ int /* MaxPlayerHealth */)
inline FOnPlayerHealthChangeDelegate OnPlayerHealthChange;


DECLARE_MULTICAST_DELEGATE_OneParam(FSetRunStatePlayerVariables, APlayerCharacter* /* PlayerCharacter */)
inline FSetRunStatePlayerVariables SetRunStatePlayerVariablesDelegate;
DECLARE_MULTICAST_DELEGATE_OneParam(FSaveRunStatePlayerVariables, APlayerCharacter* /* PlayerCharacter */)
inline FSaveRunStatePlayerVariables SaveRunStatePlayerVariablesDelegate;
