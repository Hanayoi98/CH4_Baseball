#include "UI/BBChatInput.h"

#include "Components/EditableTextBox.h"
#include "Player/BBPlayerController.h"

void UBBChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UBBChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UBBChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		ABBPlayerController* OwningBBPlayerController = Cast<ABBPlayerController>(GetOwningPlayer());
		if (IsValid(OwningBBPlayerController) == true)
		{
			OwningBBPlayerController->SetChatMessageString(Text.ToString());

			EditableTextBox_ChatInput->SetText(FText());
		}
	}
}