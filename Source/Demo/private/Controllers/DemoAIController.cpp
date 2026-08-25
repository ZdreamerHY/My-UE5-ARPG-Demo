// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DemoAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


//构造函数创建PathFollowingComponent时替换为CrowdFollowingComponent
ADemoAIController::ADemoAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{

	//只检测敌人，不检测队友和中立
	EnemySenseConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig"));
	EnemySenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	EnemySenseConfig->DetectionByAffiliation.bDetectFriendlies = false;
	EnemySenseConfig->DetectionByAffiliation.bDetectNeutrals=false;
	EnemySenseConfig->SightRadius=5000.0f;
	EnemySenseConfig->LoseSightRadius=0.0f;
	EnemySenseConfig->PeripheralVisionAngleDegrees=180.0f;

	EnemyPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*EnemySenseConfig);
	//设置视觉为主导
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	//目标更新时触发回调函数
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&ThisClass::OnEnemyPerceptionUpdated);

	//划分阵营
	SetGenericTeamId(FGenericTeamId(1));
}

void ADemoAIController::BeginPlay()
{
	Super::BeginPlay();

	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		//是否开启群体模拟
		CrowdComp->SetCrowdSimulationState(bEnableCrowdAvoidance?ECrowdSimulationState::Enabled:ECrowdSimulationState::Disabled);
		
		//绕行质量
		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
		case 2:CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
		case 3:CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
		case 4:CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
			default: break;
		}

		//设置绕行组,属于哪一组，躲避哪一组，检测范围为多大
		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionRange);
	}
}

void ADemoAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed()&&Actor)
	{
		if (UBlackboardComponent* BlackboardComponent=GetBlackboardComponent())
		{
			//行为树里的黑板资产，TargetActor键对应的值填入输入的Actor
			BlackboardComponent->SetValueAsObject(FName("TargetActor"),Actor);
		}
	}
}

ETeamAttitude::Type ADemoAIController::GetTeamAttitudeTowards(const AActor& OtherActor) const 
{
	const APawn* PawnActor = Cast<APawn>(&OtherActor);
	
	if (!PawnActor)
	{
		return ETeamAttitude::Neutral; // 非Pawn视为中立
	}
	
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnActor->GetController());
	if (!OtherTeamAgent)
	{
		// 没有队伍接口的，视为中立
		return ETeamAttitude::Neutral;
	}

	if (OtherTeamAgent->GetGenericTeamId()<GetGenericTeamId())		//要把Hero和EQS作出区分，Hero的TeamId为0
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}
