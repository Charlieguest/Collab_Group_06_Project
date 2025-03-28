#include "InventoryItem.h"


AInventoryItem::AInventoryItem()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
	
	_ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Item Mesh"));
	_ItemMesh->SetupAttachment(_Root);

}

void AInventoryItem::interact_Implementation()
{
	IInteract::interact_Implementation();
	this->Destroy();
}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}
