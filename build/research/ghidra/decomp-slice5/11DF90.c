// image offset 0x11DF90 address 7ff7a32adf90

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32adf90(longlong param_1)

{
  longlong lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  int iVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  longlong lVar11;
  int iVar12;
  int iVar13;
  undefined8 *puVar14;
  float fVar15;
  undefined1 auStack_1308 [32];
  undefined4 local_12e8 [2];
  undefined8 local_12e0 [599];
  ulonglong local_28;
  undefined8 local_20;
  
  local_20 = 0x7ff7a32adfa8;
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1308;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 3)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar7 = FUN_7ff7a3468d90(param_1);
    if ((iVar7 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar7 = FUN_7ff7a3468d90(param_1);
      if ((iVar7 != 0) && (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)))
      {
        iVar7 = FUN_7ff7a3468d90(param_1);
        if (iVar7 != 0) goto LAB_7ff7a32ae02b;
      }
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ae02b:
  uVar8 = *(ulonglong *)(param_1 + 0x50);
  iVar7 = 0;
  uVar10 = *(ulonglong *)(param_1 + 0x48);
  if (uVar8 < uVar10) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1,uVar8);
    uVar8 = *(ulonglong *)(param_1 + 0x50);
    uVar10 = *(ulonglong *)(param_1 + 0x48);
    iVar12 = (int)fVar15;
  }
  else {
    iVar12 = 0;
  }
  if (uVar8 + 0x10 < uVar10) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1);
    uVar8 = *(ulonglong *)(param_1 + 0x50);
    uVar10 = *(ulonglong *)(param_1 + 0x48);
    iVar13 = (int)fVar15;
  }
  else {
    iVar13 = 0;
  }
  if (uVar8 + 0x20 < uVar10) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1);
    iVar7 = (int)fVar15;
  }
  iVar7 = FUN_7ff7a34047e0(iVar12,local_12e8,iVar13,iVar7);
  lVar11 = (longlong)iVar7;
  FUN_7ff7a324d6e0(1,iVar7,0,param_1);
  if (0 < iVar7) {
    iVar7 = 1;
    puVar14 = local_12e0;
    do {
      FUN_7ff7a324d6e0(iVar7,0,2,DAT_7ff7a4d63d08);
      thunk_FUN_7ff7a325af40(param_1,*(undefined4 *)(puVar14 + -1));
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
      FUN_7ff7a325c620("quantity",*(undefined4 *)puVar14,DAT_7ff7a4d63d08);
      uVar6 = DAT_7ff7a4d63d08;
      uVar9 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb10c,*puVar14);
      FUN_7ff7a325c810("expiryDuration",uVar9,uVar6);
      uVar6 = DAT_7ff7a4d63d08;
      uVar9 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc32b4,*(undefined4 *)puVar14);
      FUN_7ff7a325c810("expireDateTime",uVar9,uVar6);
      FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
      iVar7 = iVar7 + 1;
      puVar14 = puVar14 + 2;
      lVar11 = lVar11 + -1;
    } while (lVar11 != 0);
  }
  return 1;
}

