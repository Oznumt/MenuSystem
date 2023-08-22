// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerPluginSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

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
	if (!SessionInterface.IsValid())
	{
		return;
	}
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);

	}
	//Store the delegate in a FDelegateHandle so we can later remove it from the delegate list
	CreateSessionCompleteDelegateHandle =  SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		// Broadcast my own custom delegate
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}


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
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

	}
	MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);

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