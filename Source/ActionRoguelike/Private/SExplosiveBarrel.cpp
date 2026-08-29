// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMeshComp);

	RadialForceComp->SetAutoActivate(false);

	RadialForceComp->Radius = 750.f;
	RadialForceComp->ImpulseStrength = 2500.f;
	// 忽略物体质量，使力更容易有效果
	RadialForceComp->bImpulseVelChange = true;
	// 可选，原有的构造函数就会自动添加四个类型
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 绑定事件
	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);

}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

