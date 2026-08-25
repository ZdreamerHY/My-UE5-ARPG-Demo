// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem/DemoGameplayTags.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"


namespace DemoGameplayTags
{
	//输入Tag
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_TaiDao, "InputTag.Equip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip_TaiDao,"InputTag.UnEquip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light,"InputTag.Attack.Light")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy,"InputTag.Attack.Heavy")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll,"InputTag.Roll")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Execute,"InputTag.Execute")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld,"InputTag.MustBeHeld")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block,"InputTag.MustBeHeld.Block")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable,"InputTag.Toggleable")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_LockTarget,"InputTag.Toggleable.LockTarget")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeTarget,"InputTag.ChangeTarget")
	
	//角色Tag
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_TaiDao, "Player.Weapon.TaiDao")

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_TaiDao,"Player.Ability.Equip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_TaiDao,"Player.Ability.UnEquip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light,"Player.Ability.Attack.Light")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy,"Player.Ability.Attack.Heavy")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll,"Player.Ability.Roll")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block,"Player.Ability.Block")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LockTarget,"Player.Ability.LockTarget")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ChangeTarget,"Player.Ability.ChangeTarget")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Execute,"Player.Ability.Execute")
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_TaiDao,"Player.Event.Equip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_TaiDao,"Player.Event.UnEquip.TaiDao")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock,"Player.Event.SuccessfulBlock")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ChangeTarget,"Player.Event.ChangeTarget")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Execute,"Player.Event.Execute")
	
	UE_DEFINE_GAMEPLAY_TAG(Player_AttackTypre_Light,"Player.AttackType.Light")
	UE_DEFINE_GAMEPLAY_TAG(Player_AttackTypre_Heavy,"Player.AttackType.Heavy")

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling,"Player.Status.Rolling")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking,"Player.Status.Blocking")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_LockTarget,"Player.Status.LockTarget")
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Invincible,"Player.Status.Invincible")
	
	//敌人Tag
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee,"Enemy.Ability.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged,"Enemy.Ability.Ranged")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing,"Enemy.Status.Strafing")
	
	//连招Tag
	UE_DEFINE_GAMEPLAY_TAG(Combo_Cut, "Combo.Cut")
	UE_DEFINE_GAMEPLAY_TAG(Combo_Input, "Combo.Input")

	//共享Tag
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit,"Shared.Event.MeleeHit")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact,"Shared.Event.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_ExeEnd,"Shared.Event.ExeEnd")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death,"Shared.Ability.Death")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact,"Shared.Ability.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Stun,"Shared.Ability.Stun")
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage,"Shared.SetByCaller.BaseDamage")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead,"Shared.Status.Dead")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Stun,"Shared.Status.Stun")
}
