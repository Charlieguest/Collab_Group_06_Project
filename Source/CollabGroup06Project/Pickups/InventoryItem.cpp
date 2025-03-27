#include "InventoryItem.h"


AInventoryItem::AInventoryItem()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
	
	_ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Item Mesh"));
	_ItemMesh->SetupAttachment(_Root);

}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}