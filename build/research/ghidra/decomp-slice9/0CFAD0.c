// image offset 0xCFAD0 address 7ff7a325fad0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 * FUN_7ff7a325fad0(int param_1,int param_2,undefined8 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined1 *puVar6;
  char *pcVar7;
  undefined1 auStack_638 [32];
  ulonglong local_618;
  int local_610;
  int *local_608;
  int local_5f8;
  undefined4 uStack_5f4;
  undefined8 local_5f0;
  undefined8 local_5e8 [2];
  undefined8 local_5d8;
  undefined8 local_5d0;
  char *local_5c8;
  undefined8 local_5c0;
  undefined8 local_5b8;
  undefined8 uStack_5b0;
  undefined8 local_5a8;
  undefined8 uStack_5a0;
  undefined8 local_598;
  undefined8 uStack_590;
  undefined1 local_588 [48];
  undefined1 local_558 [48];
  char local_528 [256];
  undefined1 local_428 [1024];
  ulonglong local_28;

  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_638;
  if ((param_1 != -1) && (cVar1 = FUN_7ff7a391a170(), cVar1 != '\0')) {
    param_1 = FUN_7ff7a3631610();
  }
  FUN_7ff7a38f34d0("mp/unlocktable.csv",local_5e8);
  if (param_2 != 0) {
    FUN_7ff7a38f34d0("mp/statstable.csv",&local_5f0);
    uVar4 = FUN_7ff7a37e2610(param_2);
    param_3 = FUN_7ff7a38f3560(local_5f0,0x12,uVar4);
  }
  iVar2 = FUN_7ff7a38f3700(local_5e8[0],0,param_3);
  if (iVar2 < 0) {
LAB_7ff7a325fde2:
    return &DAT_7ff7a3cbd562;
  }
  uVar3 = FUN_7ff7a325f390(param_1);
  local_618 = local_618 & 0xffffffffffffff00;
  cVar1 = FUN_7ff7a331dcf0(local_558,param_1,uVar3,4);
  if (cVar1 == '\0') goto LAB_7ff7a325fde2;
  uVar3 = FUN_7ff7a325f390(param_1);
  local_618 = local_618 & 0xffffffffffffff00;
  cVar1 = FUN_7ff7a331dcf0(local_588,param_1,uVar3,0);
  if (cVar1 == '\0') goto LAB_7ff7a325fde2;
  local_608 = &local_5f8;
  local_618 = local_5e8[0];
  local_610 = iVar2;
  uVar3 = thunk_EXT_FUN_7ff7a3180553(param_2,param_1,local_558,local_588);
  switch(uVar3) {
  case 1:
    FUN_7ff7a38f34d0("mp/allChallengesTable.csv",&local_5f0);
    _itoa(local_5f8 / 100,local_528,10);
    uVar4 = FUN_7ff7a38f3560(local_5f0,0x1b,local_528);
    uVar5 = FUN_7ff7a38f3560(local_5f0,0x1b,local_528,(local_5f8 % 100) * 2 + 7);
    uVar4 = FUN_7ff7a37f1c60(uVar4);
    puVar6 = (undefined1 *)FUN_7ff7a37f1a10(uVar4,uVar5);
    break;
  case 2:
    uVar4 = FUN_7ff7a37e9f20(local_5f8,5);
    local_5d8 = 2;
    local_5c0 = 0;
    local_5b8 = 0;
    uStack_5b0 = 0;
    local_5a8 = 0;
    uStack_5a0 = 0;
    local_598 = 0;
    uStack_590 = 0;
    local_5d0 = FUN_7ff7a37f1c60(uVar4);
    local_5c8 = _itoa(local_5f8 + 1,local_528,10);
    uVar4 = FUN_7ff7a37f1c60("LUA_MENU_ITEM_LEVEL_UNLOCK_DESC");
    FUN_7ff7a37f1aa0(uVar4,&local_5d8,local_428,0x400);
    puVar6 = local_428;
    break;
  case 3:
    puVar6 = (undefined1 *)FUN_7ff7a37f1c60("LUA_MENU_ITEM_TOKEN_UNLOCK_DESC");
    break;
  default:
    puVar6 = &DAT_7ff7a3cbd562;
    break;
  case 5:
    puVar6 = (undefined1 *)FUN_7ff7a37f1c60("LUA_MENU_ITEM_ALL_LOCKED_DESC");
    break;
  case 6:
    puVar6 = (undefined1 *)FUN_7ff7a37f1c60("LUA_MENU_ITEM_EXPIRED_DESC");
    break;
  case 0xe:
    pcVar7 = "LUA_MENU_ITEM_PRESTIGE_UNLOCK_DESC";
    goto LAB_7ff7a325fd47;
  case 0xf:
    pcVar7 = "LUA_MENU_ITEM_MASTER_PRESTIGE_UNLOCK_DESC";
LAB_7ff7a325fd47:
    uVar4 = FUN_7ff7a37f1c60(pcVar7);
    pcVar7 = _itoa(local_5f8,local_528,10);
    puVar6 = (undefined1 *)FUN_7ff7a37f1a10(uVar4,pcVar7);
    break;
  case 0x10:
    if (CONCAT44(uStack_5f4,local_5f8) == 0) {
      uVar4 = FUN_7ff7a37f1c60("LUA_MENU_ITEM_DLC_UNLOCK_DESC");
      puVar6 = (undefined1 *)FUN_7ff7a37f1a10(uVar4,&DAT_7ff7a3cbd562);
    }
    else {
      puVar6 = (undefined1 *)FUN_7ff7a37f1c60("LUA_MENU_ITEM_DLC_EARLY_ACCESS_UNLOCK_DESC");
    }
  }
  return puVar6;
}
