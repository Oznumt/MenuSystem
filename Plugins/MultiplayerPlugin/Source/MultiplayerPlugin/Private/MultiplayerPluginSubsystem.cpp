// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPluginSubsystem.h"
#include "OnlineSubsystem.h"

UMultiplayerPluginSubsystem::UMultiplayerPluginSubsystem() :
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}

}

void UMultiplayerPluginSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{

}

void UMultiplayerPluginSubsystem::FindSessions(int32 MaxSearchResults)
{

}

void UMultiplayerPluginSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{

}

void UMultiplayerPluginSubsystem::DestroySession()
{

}

void UMultiplayerPluginSubsystem::StartSession()
{

}

void UMultiplayerPluginSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerPluginSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{

}

void UMultiplayerPluginSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{

}

void UMultiplayerPluginSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{

}

void UMultiplayerPluginSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{

}