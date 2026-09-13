// image offset 0x120B60 address 7ff7a32b0b60

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32b0b60(longlong param_1)

{
  longlong lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  float fVar10;
  undefined1 auStack_88 [32];
  undefined4 local_68 [20];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_88;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 1
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar6 = FUN_7ff7a3468d90(param_1), iVar6 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar9 = 0;
  uVar7 = uVar9;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar10 = (float)FUN_7ff7a3469aa0(param_1);
    uVar7 = (int)fVar10;
  }
  uVar7 = FUN_7ff7a343ee20(uVar7,local_68,10);
  FUN_7ff7a324d6e0(1,uVar7,0,param_1);
  if (uVar7 != 0) {
    puVar8 = local_68;
    do {
      uVar9 = uVar9 + 1;
      FUN_7ff7a324d6e0(uVar9,0,2,DAT_7ff7a4d63d08);
      thunk_FUN_7ff7a325af40(param_1,*puVar8);
      if (*(ulonglong *)(param_1 + 0x58) < *(longlong *)(param_1 + 0x48) + 0x20U) {
        FUN_7ff7a3466cd0(param_1 + 0x18,param_1,2);
      }
      FUN_7ff7a3294620(param_1,&DAT_7ff7a3cd0848,4);
      lVar1 = *(longlong *)(param_1 + 0x48);
      uVar2 = *(undefined4 *)(lVar1 + -0x10);
      uVar3 = *(undefined4 *)(lVar1 + -0xc);
      uVar4 = *(undefined4 *)(lVar1 + -8);
      uVar5 = *(undefined4 *)(lVar1 + -4);
      *(undefined4 *)(lVar1 + -0x10) = *(undefined4 *)(lVar1 + -0x20);
      *(undefined4 *)(lVar1 + -0xc) = *(undefined4 *)(lVar1 + -0x1c);
      *(undefined4 *)(lVar1 + -8) = *(undefined4 *)(lVar1 + -0x18);
      *(undefined4 *)(lVar1 + -4) = *(undefined4 *)(lVar1 + -0x14);
      *(undefined4 *)(lVar1 + -0x20) = uVar2;
      *(undefined4 *)(lVar1 + -0x1c) = uVar3;
      *(undefined4 *)(lVar1 + -0x18) = uVar4;
      *(undefined4 *)(lVar1 + -0x14) = uVar5;
      *(longlong *)(param_1 + 0x48) = lVar1;
      FUN_7ff7a34696b0(param_1,lVar1 + -0x30);
      *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x20;
      FUN_7ff7a325c620("quantity",puVar8[1],DAT_7ff7a4d63d08);
      FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
      puVar8 = puVar8 + 2;
    } while (uVar9 < uVar7);
  }
  return 1;
}

