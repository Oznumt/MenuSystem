// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerPluginSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGIN_API UMultiplayerPluginSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMultiplayerPluginSubsystem();
protected:

private:

	IOnlineSessionPtr SessionInterface;
};
