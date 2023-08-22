// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerPluginSubsystem.h"
#include "OnlineSessionSettings.h"


void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerPluginSubsystem = GameInstance->GetSubsystem<UMultiplayerPluginSubsystem>();
	}

	if (MultiplayerPluginSubsystem)
	{
		MultiplayerPluginSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerPluginSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		MultiplayerPluginSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerPluginSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerPluginSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}

}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("Session created successfully!"))
			);
		}
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");

		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failed to create session!"))
			);
		}

	}

}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{

}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{

}

void UMenu::OnDestroySession(bool bWasSuccessful)
{

}

void UMenu::OnStartSession(bool bWasSuccessful)
{

}

void UMenu::HostButtonClicked()
{

	if (MultiplayerPluginSubsystem)
	{
		MultiplayerPluginSubsystem->CreateSession(NumPublicConnections, MatchType);
		
	}

}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Yellow,
			FString(TEXT("Join Button Clicked"))
		);
	}

}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);

		}
	}

}
