// image offset 0x120390 address 7ff7a32b0390

undefined8 FUN_7ff7a32b0390(longlong param_1)

{
  byte bVar1;
  longlong lVar2;
  bool bVar3;
  undefined8 uVar4;
  bool bVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint *puVar9;
  undefined8 *puVar10;
  uint uVar11;
  undefined4 *puVar12;
  longlong lVar13;
  longlong local_res8;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined1 local_28 [16];
  
  lVar13 = 0;
  puVar9 = (uint *)(*(longlong *)(param_1 + 0x50) + 0x10);
  bVar5 = false;
  if ((puVar9 < *(uint **)(param_1 + 0x48)) &&
     ((uVar11 = *puVar9 & 0xf, uVar11 == 5 || (uVar11 == 0xc)))) {
    bVar5 = true;
  }
  if ((((int)((longlong)*(uint **)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 1) ||
      (iVar6 = thunk_FUN_7ff7a3294bb0(param_1,1), iVar6 == 0)) &&
     ((((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 2 ||
       ((iVar6 = thunk_FUN_7ff7a3294bb0(param_1,1), iVar6 == 0 ||
        (puVar9 = (uint *)(*(longlong *)(param_1 + 0x50) + 0x10),
        *(uint **)(param_1 + 0x48) <= puVar9)))) ||
      ((uVar11 = *puVar9 & 0xf, uVar11 != 5 && (uVar11 != 0xc)))))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar7 = FUN_7ff7a325cb30(param_1,1);
  local_res8 = 0;
  FUN_7ff7a34097e0(uVar7,&local_res8);
  if (local_res8 == 0) {
    if (!bVar5) {
      FUN_7ff7a324d740("items",0,0,param_1);
    }
    puVar12 = *(undefined4 **)(param_1 + 0x48);
    puVar12[2] = 0;
    *puVar12 = 3;
    *(undefined4 **)(param_1 + 0x48) = puVar12 + 4;
  }
  else {
    if (!bVar5) {
      FUN_7ff7a324d740("items",*(undefined1 *)(local_res8 + 0x244),0,param_1);
    }
    if (*(char *)(local_res8 + 0x244) == '\0') {
      puVar12 = *(undefined4 **)(param_1 + 0x48);
    }
    else {
      iVar6 = 1;
      do {
        if (bVar5) {
          puVar12 = *(undefined4 **)(param_1 + 0x48);
          *puVar12 = 3;
          puVar12[2] = (float)iVar6;
          *(undefined4 **)(param_1 + 0x48) = puVar12 + 4;
          local_38 = *(undefined8 *)(puVar12 + -4);
          uStack_30 = *(undefined8 *)(puVar12 + -2);
          puVar10 = (undefined8 *)FUN_7ff7a3468aa0(local_28,param_1,&local_38,puVar12);
          uVar4 = puVar10[1];
          lVar2 = *(longlong *)(param_1 + 0x48);
          *(undefined8 *)(lVar2 + -0x10) = *puVar10;
          *(undefined8 *)(lVar2 + -8) = uVar4;
        }
        else {
          FUN_7ff7a324d6e0(iVar6,0,2,DAT_7ff7a4d63d08);
        }
        FUN_7ff7a325c510(&DAT_7ff7a3cd0848,*(undefined4 *)(lVar13 + 0x30 + local_res8),
                         DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("quantity",*(undefined4 *)(lVar13 + 0x34 + local_res8),DAT_7ff7a4d63d08);
        if (bVar5) {
          iVar8 = (int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4);
          if (0 < iVar8) {
            iVar8 = 1;
          }
          puVar12 = (undefined4 *)(*(longlong *)(param_1 + 0x48) + (longlong)iVar8 * -0x10);
          *(undefined4 **)(param_1 + 0x48) = puVar12;
        }
        else {
          FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
          puVar12 = *(undefined4 **)(param_1 + 0x48);
        }
        lVar13 = lVar13 + 0x38;
        bVar3 = iVar6 < (int)(uint)*(byte *)(local_res8 + 0x244);
        iVar6 = iVar6 + 1;
      } while (bVar3);
    }
    bVar1 = *(byte *)(local_res8 + 0x244);
    *puVar12 = 3;
    puVar12[2] = (float)bVar1;
    *(undefined4 **)(param_1 + 0x48) = puVar12 + 4;
  }
  return 2;
}

