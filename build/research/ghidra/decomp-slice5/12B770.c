// image offset 0x12B770 address 7ff7a32bb770

undefined8 FUN_7ff7a32bb770(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  longlong lVar7;
  ulonglong uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  float fVar12;
  int local_res8 [2];
  undefined1 local_res10 [8];
  ulonglong in_stack_ffffffffffffff78;
  undefined1 local_68 [4];
  undefined4 local_64;
  undefined4 local_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined1 local_48 [16];
  undefined8 local_38;
  
  local_68[0] = 0;
  uVar10 = 0;
  uVar11 = 0;
  local_64 = 0;
  local_60 = 0xffffffff;
  local_58 = 0;
  uStack_50 = 0;
  if ((((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) <
          4) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
       (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 == 0)) ||
      ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U ||
       (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 == 0)))) ||
     ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U ||
      (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 == 0)))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar12 = (float)FUN_7ff7a3469aa0(param_1);
    local_res8[0] = (int)fVar12;
    if (local_res8[0] == -1) {
      FUN_7ff7a34a67f0(local_res10,local_res8);
    }
  }
  else {
    local_res8[0] = 0;
  }
  lVar7 = *(longlong *)(param_1 + 0x50);
  uVar8 = *(ulonglong *)(param_1 + 0x48);
  if (lVar7 + 0x10U < uVar8) {
    fVar12 = (float)FUN_7ff7a3469aa0(param_1);
    lVar7 = *(longlong *)(param_1 + 0x50);
    uVar8 = *(ulonglong *)(param_1 + 0x48);
    uVar10 = (uint)fVar12;
  }
  if (lVar7 + 0x20U < uVar8) {
    fVar12 = (float)FUN_7ff7a3469aa0(param_1);
    uVar11 = (uint)fVar12;
  }
  iVar4 = FUN_7ff7a36321d0(local_res8[0]);
  if ((int)(&DAT_7ff7a4d3f4e4)[(longlong)iVar4 * 0x1ee] < 10) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    puVar1[2] = 0;
    *puVar1 = 1;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar7 = FUN_7ff7a31a5330(iVar4);
    if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x5940) == 0)) {
      puVar1 = *(undefined4 **)(param_1 + 0x48);
      puVar1[2] = 0;
      *puVar1 = 1;
    }
    else {
      uVar5 = FUN_7ff7a325f390(local_res8[0]);
      cVar3 = FUN_7ff7a331dcf0(local_48,local_res8[0],uVar5,6,
                               in_stack_ffffffffffffff78 & 0xffffffffffffff00);
      puVar1 = *(undefined4 **)(param_1 + 0x48);
      if (cVar3 == '\0') {
        puVar1[2] = 0;
        *puVar1 = 1;
      }
      else {
        iVar4 = (int)((longlong)puVar1 - *(longlong *)(param_1 + 0x50) >> 4);
        FUN_7ff7a32d0ec0(param_1,-(iVar4 + -3),iVar4 + -3,local_38,local_68,6,1);
        uVar6 = FUN_7ff7a3bac860(local_68);
        iVar4 = FUN_7ff7a325f700();
        if (uVar11 < iVar4 - uVar6) {
          puVar1 = *(undefined4 **)(param_1 + 0x48);
          puVar1[2] = 1;
          *puVar1 = 1;
        }
        else {
          uVar9 = uVar6 % uVar11;
          iVar2 = uVar11 - uVar9;
          if (uVar9 <= uVar10) {
            iVar2 = -uVar9;
          }
          puVar1 = *(undefined4 **)(param_1 + 0x48);
          *puVar1 = 1;
          if (iVar4 - uVar6 < iVar2 + uVar10) {
            puVar1[2] = 0;
          }
          else {
            puVar1[2] = 1;
          }
        }
      }
    }
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  return 1;
}

