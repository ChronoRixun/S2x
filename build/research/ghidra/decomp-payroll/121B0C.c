// image offset 0x121B0C address 7ff7a32b1b0c

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

undefined8 FUN_7ff7a32b1a00(longlong param_1)

{
  undefined4 *puVar1;
  longlong lVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  undefined8 *puVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  float fVar16;
  undefined1 auStack_1308 [32];
  undefined8 auStack_12e8 [4];
  undefined4 local_12c8 [1192];
  ulonglong local_28;
  
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1308;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 1
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar9 = FUN_7ff7a3468d90(param_1), iVar9 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar13 = 0;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar16 = (float)FUN_7ff7a3469aa0(param_1);
    iVar9 = (int)fVar16;
  }
  else {
    iVar9 = 0;
  }
  puVar12 = (undefined8 *)(&DAT_7ff7a8e24c60 + (longlong)iVar9 * 0x1908);
  if ((&DAT_7ff7a8e26560)[(longlong)iVar9 * 0x1908] == '\0') {
    FUN_7ff7a324d6e0(1,0,0,param_1);
  }
  else {
    uVar15 = 0;
    uVar14 = 0;
    do {
      if (*(int *)((longlong)puVar12 + 0xc) != -1) {
        if (99 < uVar14) break;
        uVar7 = puVar12[1];
        uVar10 = (ulonglong)uVar14;
        uVar11 = puVar12[2];
        uVar8 = puVar12[3];
        uVar14 = uVar14 + 1;
        auStack_12e8[uVar10 * 6] = *puVar12;
        auStack_12e8[uVar10 * 6 + 1] = uVar7;
        uVar3 = *(undefined4 *)(puVar12 + 4);
        uVar4 = *(undefined4 *)((longlong)puVar12 + 0x24);
        uVar5 = *(undefined4 *)(puVar12 + 5);
        uVar6 = *(undefined4 *)((longlong)puVar12 + 0x2c);
        auStack_12e8[uVar10 * 6 + 2] = uVar11;
        auStack_12e8[uVar10 * 6 + 3] = uVar8;
        local_12c8[uVar10 * 0xc] = uVar3;
        local_12c8[uVar10 * 0xc + 1] = uVar4;
        local_12c8[uVar10 * 0xc + 2] = uVar5;
        local_12c8[uVar10 * 0xc + 3] = uVar6;
      }
      uVar15 = uVar15 + 1;
      puVar12 = puVar12 + 6;
    } while (uVar15 < 100);
    FUN_7ff7a324d6e0(1,uVar14,0,param_1);
    if (uVar14 != 0) {
      puVar12 = auStack_12e8 + 1;
      do {
        uVar13 = uVar13 + 1;
        FUN_7ff7a324d6e0(uVar13,0,2,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,*(undefined4 *)((longlong)puVar12 + 4),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,*(undefined4 *)puVar12,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("target",*(undefined4 *)(puVar12 + 1),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("status",*(undefined4 *)(puVar12 + 4),DAT_7ff7a4d63d08);
        FUN_7ff7a325c580("timeLimit",*(undefined4 *)((longlong)puVar12 + 0xfffffffffffffffc),
                         DAT_7ff7a4d63d08);
        uVar7 = DAT_7ff7a4d63d08;
        uVar11 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb22c,puVar12[2]);
        FUN_7ff7a325c810("expirationTimestamp",uVar11,uVar7);
        puVar1 = (undefined4 *)puVar12[3];
        if (puVar1 != (undefined4 *)0x0) {
          FUN_7ff7a324d7b0("reward",param_1);
          FUN_7ff7a325c870("productID",*puVar1,param_1);
          thunk_FUN_7ff7a325af40(param_1,puVar1[1]);
          if (*(ulonglong *)(param_1 + 0x58) < *(longlong *)(param_1 + 0x48) + 0x20U) {
            FUN_7ff7a3466cd0(param_1 + 0x18,param_1,2);
          }
          FUN_7ff7a3294620(param_1,"itemID",6);
          lVar2 = *(longlong *)(param_1 + 0x48);
          uVar3 = *(undefined4 *)(lVar2 + -0x10);
          uVar4 = *(undefined4 *)(lVar2 + -0xc);
          uVar5 = *(undefined4 *)(lVar2 + -8);
          uVar6 = *(undefined4 *)(lVar2 + -4);
          *(undefined4 *)(lVar2 + -0x10) = *(undefined4 *)(lVar2 + -0x20);
          *(undefined4 *)(lVar2 + -0xc) = *(undefined4 *)(lVar2 + -0x1c);
          *(undefined4 *)(lVar2 + -8) = *(undefined4 *)(lVar2 + -0x18);
          *(undefined4 *)(lVar2 + -4) = *(undefined4 *)(lVar2 + -0x14);
          *(undefined4 *)(lVar2 + -0x20) = uVar3;
          *(undefined4 *)(lVar2 + -0x1c) = uVar4;
          *(undefined4 *)(lVar2 + -0x18) = uVar5;
          *(undefined4 *)(lVar2 + -0x14) = uVar6;
          *(longlong *)(param_1 + 0x48) = lVar2;
          FUN_7ff7a34696b0(param_1,lVar2 + -0x30);
          *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x20;
          FUN_7ff7a325c620("currencyID",puVar1[2],DAT_7ff7a4d63d08);
          FUN_7ff7a325c620("currencyAmount",puVar1[3],DAT_7ff7a4d63d08);
          FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        }
        FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        puVar12 = puVar12 + 6;
      } while (uVar13 < uVar14);
    }
  }
  return 1;
}

