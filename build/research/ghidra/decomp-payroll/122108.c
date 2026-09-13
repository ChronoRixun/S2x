// image offset 0x122108 address 7ff7a32b2108

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

undefined8 FUN_7ff7a32b1f40(longlong param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  uint *puVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  undefined8 *puVar20;
  float fVar21;
  undefined1 auStack_fa48 [32];
  undefined8 auStack_fa28 [4];
  uint local_fa08 [4];
  ulonglong auStack_f9f8 [7996];
  
  auStack_f9f8[0x1f3b] = 0x7ff7a32b1f4e;
  auStack_f9f8[0x1f3a] = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_fa48;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) < 2)
     || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) {
LAB_7ff7a32b1fa8:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  else {
    iVar9 = FUN_7ff7a3468d90(param_1);
    if ((iVar9 == 0) ||
       ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U ||
        (iVar9 = FUN_7ff7a3468d90(param_1), iVar9 == 0)))) goto LAB_7ff7a32b1fa8;
  }
  uVar11 = *(ulonglong *)(param_1 + 0x50);
  uVar18 = 0;
  uVar14 = *(ulonglong *)(param_1 + 0x48);
  if (uVar11 < uVar14) {
    fVar21 = (float)FUN_7ff7a3469aa0(param_1,uVar11);
    uVar11 = *(ulonglong *)(param_1 + 0x50);
    uVar14 = *(ulonglong *)(param_1 + 0x48);
    iVar9 = (int)fVar21;
  }
  else {
    iVar9 = 0;
  }
  if (uVar11 + 0x10 < uVar14) {
    fVar21 = (float)FUN_7ff7a3469aa0(param_1);
    if ((int)fVar21 != 0) {
      uVar17 = 1 << ((byte)(int)fVar21 & 0x1f);
      goto LAB_7ff7a32b201f;
    }
  }
  cVar8 = FUN_7ff7a3248cb0();
  uVar17 = 0x209e;
  if (cVar8 != '\0') {
    uVar17 = 0x1f00;
  }
LAB_7ff7a32b201f:
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50)) >> 4) == 3)
      && (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48))) &&
     (iVar10 = FUN_7ff7a3468d90(param_1), iVar10 != 0)) {
    if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
      fVar21 = (float)FUN_7ff7a3469aa0(param_1);
      uVar17 = (uint)fVar21;
    }
    else {
      uVar17 = 0;
    }
  }
  if ((&DAT_7ff7a9234080)[(longlong)iVar9 * 0x13890] == '\0') {
    FUN_7ff7a324d6e0(1,0,0,param_1);
  }
  else {
    uVar19 = 0;
    puVar15 = (uint *)(&DAT_7ff7a9234098 + (longlong)iVar9 * 0x13890);
    uVar16 = 0;
    do {
      if ((puVar15[1] != 0xffffffff) && ((uVar17 >> (*puVar15 & 0x1f) & 1) != 0)) {
        if (999 < uVar19) break;
        uVar6 = *(undefined8 *)puVar15;
        uVar12 = (ulonglong)uVar19;
        uVar13 = *(undefined8 *)(puVar15 + 2);
        uVar7 = *(undefined8 *)(puVar15 + 4);
        uVar19 = uVar19 + 1;
        auStack_fa28[uVar12 * 8] = *(undefined8 *)(puVar15 + -2);
        auStack_fa28[uVar12 * 8 + 1] = uVar6;
        uVar2 = puVar15[6];
        uVar3 = puVar15[7];
        uVar4 = puVar15[8];
        uVar5 = puVar15[9];
        auStack_fa28[uVar12 * 8 + 2] = uVar13;
        auStack_fa28[uVar12 * 8 + 3] = uVar7;
        uVar11 = *(ulonglong *)(puVar15 + 10);
        uVar14 = *(ulonglong *)(puVar15 + 0xc);
        local_fa08[uVar12 * 0x10] = uVar2;
        local_fa08[uVar12 * 0x10 + 1] = uVar3;
        local_fa08[uVar12 * 0x10 + 2] = uVar4;
        local_fa08[uVar12 * 0x10 + 3] = uVar5;
        auStack_f9f8[uVar12 * 8] = uVar11;
        auStack_f9f8[uVar12 * 8 + 1] = uVar14;
      }
      uVar16 = uVar16 + 1;
      puVar15 = puVar15 + 0x10;
    } while (uVar16 < 1000);
    FUN_7ff7a324d6e0(1,uVar19,0,param_1);
    if (uVar19 != 0) {
      puVar20 = auStack_fa28 + 1;
      do {
        uVar18 = uVar18 + 1;
        FUN_7ff7a324d6e0(uVar18,0,2,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,*(undefined4 *)((longlong)puVar20 + 4),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,*(undefined4 *)puVar20,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("progress",*(undefined2 *)(puVar20 + 4),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("target",*(undefined4 *)(puVar20 + 1),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("status",*(undefined4 *)(puVar20 + 6),DAT_7ff7a4d63d08);
        FUN_7ff7a325c580("timeLimit",*(undefined4 *)((longlong)puVar20 + 0xfffffffffffffffc),
                         DAT_7ff7a4d63d08);
        FUN_7ff7a325c580("timeLeft",*(undefined4 *)((longlong)puVar20 + 0x34),DAT_7ff7a4d63d08);
        uVar6 = DAT_7ff7a4d63d08;
        uVar13 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb22c,puVar20[2]);
        FUN_7ff7a325c810("expirationTimestamp",uVar13,uVar6);
        puVar1 = (undefined4 *)puVar20[3];
        if (puVar1 != (undefined4 *)0x0) {
          FUN_7ff7a324d7b0("reward",param_1);
          FUN_7ff7a325c870("productID",*puVar1,param_1);
          FUN_7ff7a325c510("itemID",puVar1[1],param_1);
          FUN_7ff7a325c620("currencyID",puVar1[2],DAT_7ff7a4d63d08);
          FUN_7ff7a325c620("currencyAmount",puVar1[3],DAT_7ff7a4d63d08);
          FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        }
        FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        puVar20 = puVar20 + 8;
      } while (uVar18 < uVar19);
    }
  }
  return 1;
}

