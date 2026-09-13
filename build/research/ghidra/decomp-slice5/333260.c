// image offset 0x333260 address 7ff7a34c3260

int FUN_7ff7a34c3260(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  longlong lVar7;
  ulonglong uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  char cVar13;
  int iVar14;
  float fVar15;
  int local_res8 [2];
  undefined1 local_res10 [8];
  
  if (((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) < 3
        ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
      (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) ||
     (((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U ||
       (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) ||
      ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U ||
       (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)))))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  iVar2 = 0;
  uVar10 = 0;
  uVar8 = *(ulonglong *)(param_1 + 0x48);
  uVar11 = 0;
  uVar12 = uVar11;
  if (uVar4 < uVar8) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1,uVar4);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar8 = *(ulonglong *)(param_1 + 0x48);
    uVar12 = (int)fVar15;
  }
  if (uVar4 + 0x10 < uVar8) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar8 = *(ulonglong *)(param_1 + 0x48);
    cVar13 = (char)(int)fVar15;
  }
  else {
    cVar13 = '\0';
  }
  iVar14 = iVar2;
  if (uVar4 + 0x20 < uVar8) {
    fVar15 = (float)FUN_7ff7a3469aa0(param_1);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar8 = *(ulonglong *)(param_1 + 0x48);
    iVar14 = (int)fVar15;
  }
  local_res8[0] = -1;
  if (uVar4 + 0x30 < uVar8) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 != 0) {
      if (*(longlong *)(param_1 + 0x50) + 0x30U < *(ulonglong *)(param_1 + 0x48)) {
        fVar15 = (float)FUN_7ff7a3469aa0(param_1);
        local_res8[0] = (int)fVar15;
      }
      else {
        local_res8[0] = 0;
      }
    }
    if (local_res8[0] < 0) goto LAB_7ff7a34c33a6;
  }
  else {
LAB_7ff7a34c33a6:
    FUN_7ff7a34a67f0(local_res10,local_res8);
  }
  uVar5 = FUN_7ff7a3600d30(0);
  iVar9 = (int)cVar13;
  iVar3 = FUN_7ff7a34ccd50(uVar5,iVar9);
  if (iVar3 != 1) {
    if (iVar3 == 2) {
      uVar5 = FUN_7ff7a360e350();
      lVar7 = FUN_7ff7a362e040(uVar5,iVar9);
    }
    else {
      if (iVar3 != 3) goto LAB_7ff7a34c3441;
      uVar6 = FUN_7ff7a3600f20(uVar5);
      if (uVar12 == 3) {
        iVar3 = FUN_7ff7a3609400(uVar6,iVar14);
        iVar2 = local_res8[0];
        if (iVar3 <= iVar9) goto LAB_7ff7a34c343c;
        uVar5 = FUN_7ff7a3600f20(uVar5);
        lVar7 = FUN_7ff7a362e3c0(uVar5,iVar2,iVar14,cVar13);
      }
      else {
        lVar7 = FUN_7ff7a362e040(uVar6,iVar9);
      }
      if (lVar7 == 0) goto LAB_7ff7a34c343c;
    }
    uVar10 = (uint)(*(int *)(lVar7 + 0x58) != 0);
  }
LAB_7ff7a34c343c:
  uVar11 = uVar10;
  iVar2 = 1;
LAB_7ff7a34c3441:
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = uVar11;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return iVar2;
}

