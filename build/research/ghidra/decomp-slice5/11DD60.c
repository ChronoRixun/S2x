// image offset 0x11DD60 address 7ff7a32add60

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32add60(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  uint *puVar3;
  uint *puVar4;
  ulonglong uVar5;
  float fVar6;
  undefined1 auStack_58 [32];
  undefined4 local_38 [2];
  undefined1 local_30 [32];
  ulonglong local_10;
  
  local_10 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_58;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2
       ) && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) &&
     (iVar1 = FUN_7ff7a3468d90(param_1), iVar1 != 0)) {
    puVar3 = *(uint **)(param_1 + 0x50);
    puVar4 = *(uint **)(param_1 + 0x48);
    if ((puVar3 + 4 < puVar4) && ((puVar3[4] & 0xf) - 3 < 2)) goto LAB_7ff7a32addde;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  puVar3 = *(uint **)(param_1 + 0x50);
  puVar4 = *(uint **)(param_1 + 0x48);
LAB_7ff7a32addde:
  uVar2 = 0;
  uVar5 = uVar2;
  if (puVar3 < puVar4) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,puVar3);
    puVar3 = *(uint **)(param_1 + 0x50);
    puVar4 = *(uint **)(param_1 + 0x48);
    uVar5 = (ulonglong)(uint)(int)fVar6;
  }
  if ((puVar4 <= puVar3 + 4) || (1 < (puVar3[4] & 0xf) - 3)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    puVar3 = *(uint **)(param_1 + 0x50);
    puVar4 = *(uint **)(param_1 + 0x48);
  }
  if (puVar3 + 4 < puVar4) {
    uVar2 = FUN_7ff7a3469740(param_1,puVar3 + 4,0);
  }
  FUN_7ff7a39c9040(uVar2,local_30);
  iVar1 = FUN_7ff7a343ecb0(uVar5,local_30,local_38,1);
  if (iVar1 == 0) {
    local_38[0] = 0;
  }
  thunk_FUN_7ff7a325af40(param_1,local_38[0]);
  return 1;
}

