// image offset 0x1213B0 address 7ff7a32b13b0

undefined8 FUN_7ff7a32b13b0(longlong param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  longlong lVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined8 uVar8;
  int iVar9;
  ulonglong uVar10;
  int *piVar11;
  undefined8 uVar12;
  ulonglong uVar13;
  uint uVar14;
  int iVar15;
  longlong lVar16;
  float fVar17;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar9 = FUN_7ff7a3468d90(param_1);
    if ((iVar9 != 0) &&
       ((*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48) &&
        (iVar9 = FUN_7ff7a3468d90(param_1), iVar9 != 0)))) goto LAB_7ff7a32b1418;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b1418:
  uVar10 = *(ulonglong *)(param_1 + 0x50);
  uVar14 = 0;
  uVar13 = *(ulonglong *)(param_1 + 0x48);
  if (uVar10 < uVar13) {
    fVar17 = (float)FUN_7ff7a3469aa0(param_1,uVar10);
    uVar10 = *(ulonglong *)(param_1 + 0x50);
    uVar13 = *(ulonglong *)(param_1 + 0x48);
    iVar9 = (int)fVar17;
  }
  else {
    iVar9 = 0;
  }
  if (uVar10 + 0x10 < uVar13) {
    fVar17 = (float)FUN_7ff7a3469aa0(param_1);
    iVar15 = (int)fVar17;
  }
  else {
    iVar15 = 0;
  }
  piVar11 = (int *)(&DAT_7ff7a923409c + (longlong)iVar9 * 0x13890);
  do {
    if (*piVar11 == iVar15) {
      if ((uVar14 != 0xffffffff) &&
         (lVar16 = (longlong)(int)uVar14 * 0x40 + (longlong)iVar9 * 0x13890,
         lVar16 != -0x7ff7a9234090)) {
        uVar14 = FUN_7ff7a325f700();
        uVar1 = *(undefined2 *)(&DAT_7ff7a92340b8 + lVar16);
        uVar2 = *(undefined4 *)(&DAT_7ff7a92340bc + lVar16);
        lVar3 = *(longlong *)(&DAT_7ff7a92340c0 + lVar16);
        FUN_7ff7a324d6e0(1,1,0,param_1);
        FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,*(undefined4 *)(&DAT_7ff7a923409c + lVar16),
                         DAT_7ff7a4d63d08);
        FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,*(undefined4 *)(&DAT_7ff7a9234098 + lVar16),
                         DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("progress",uVar1,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("fullfilledTimes",uVar2,DAT_7ff7a4d63d08);
        uVar8 = DAT_7ff7a4d63d08;
        uVar12 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb22c,*(undefined8 *)(&DAT_7ff7a92340c0 + lVar16));
        FUN_7ff7a325c810("lastCompletionTime",uVar12,uVar8);
        uVar8 = DAT_7ff7a4d63d08;
        uVar12 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb22c,(ulonglong)uVar14 - lVar3);
        FUN_7ff7a325c810("timeSinceLastCompletion",uVar12,uVar8);
        FUN_7ff7a325c580("timeLimit",*(undefined4 *)(&DAT_7ff7a9234094 + lVar16),DAT_7ff7a4d63d08);
        uVar8 = DAT_7ff7a4d63d08;
        uVar12 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb22c,*(undefined8 *)(&DAT_7ff7a92340a8 + lVar16));
        FUN_7ff7a325c810("expirationTimestamp",uVar12,uVar8);
        puVar4 = *(undefined4 **)(&DAT_7ff7a92340b0 + lVar16);
        if (puVar4 == (undefined4 *)0x0) {
          return 1;
        }
        FUN_7ff7a324d7b0("reward",param_1);
        FUN_7ff7a325c870("productID",*puVar4,param_1);
        thunk_FUN_7ff7a325af40(param_1,puVar4[1]);
        if (*(ulonglong *)(param_1 + 0x58) < *(longlong *)(param_1 + 0x48) + 0x20U) {
          FUN_7ff7a3466cd0(param_1 + 0x18,param_1,2);
        }
        FUN_7ff7a3294620(param_1,"itemID",6);
        lVar16 = *(longlong *)(param_1 + 0x48);
        uVar2 = *(undefined4 *)(lVar16 + -0x10);
        uVar5 = *(undefined4 *)(lVar16 + -0xc);
        uVar6 = *(undefined4 *)(lVar16 + -8);
        uVar7 = *(undefined4 *)(lVar16 + -4);
        *(undefined4 *)(lVar16 + -0x10) = *(undefined4 *)(lVar16 + -0x20);
        *(undefined4 *)(lVar16 + -0xc) = *(undefined4 *)(lVar16 + -0x1c);
        *(undefined4 *)(lVar16 + -8) = *(undefined4 *)(lVar16 + -0x18);
        *(undefined4 *)(lVar16 + -4) = *(undefined4 *)(lVar16 + -0x14);
        *(undefined4 *)(lVar16 + -0x20) = uVar2;
        *(undefined4 *)(lVar16 + -0x1c) = uVar5;
        *(undefined4 *)(lVar16 + -0x18) = uVar6;
        *(undefined4 *)(lVar16 + -0x14) = uVar7;
        *(longlong *)(param_1 + 0x48) = lVar16;
        FUN_7ff7a34696b0(param_1,lVar16 + -0x30);
        *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x20;
        FUN_7ff7a325c620("currencyID",puVar4[2],DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("currencyAmount",puVar4[3],DAT_7ff7a4d63d08);
        FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        return 1;
      }
      break;
    }
    uVar14 = uVar14 + 1;
    piVar11 = piVar11 + 0x10;
  } while (uVar14 < 1000);
  FUN_7ff7a324d6e0(1,1,0,param_1);
  FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,iVar15,DAT_7ff7a4d63d08);
  FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,0xffff,DAT_7ff7a4d63d08);
  FUN_7ff7a325c620("progress",0,DAT_7ff7a4d63d08);
  FUN_7ff7a325c620("fullfilledTimes",0,DAT_7ff7a4d63d08);
  FUN_7ff7a325c810("lastCompletionTime",&DAT_7ff7a3cc236c,DAT_7ff7a4d63d08);
  FUN_7ff7a325c810("timeSinceLastCompletion",&DAT_7ff7a3cc236c,DAT_7ff7a4d63d08);
  return 1;
}

