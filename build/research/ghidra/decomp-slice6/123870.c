// image offset 0x123870 address 7ff7a32b3870

undefined8 FUN_7ff7a32b3870(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  float fVar8;
  
  if (((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) !=
         2) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
      (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) ||
     ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U ||
      (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar5 = *(ulonglong *)(param_1 + 0x50);
  iVar2 = 0;
  uVar7 = *(ulonglong *)(param_1 + 0x48);
  if (uVar5 < uVar7) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1,uVar5);
    uVar5 = *(ulonglong *)(param_1 + 0x50);
    uVar7 = *(ulonglong *)(param_1 + 0x48);
    iVar3 = (int)fVar8;
  }
  else {
    iVar3 = 0;
  }
  if (uVar5 + 0x10 < uVar7) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar8;
  }
  iVar3 = FUN_7ff7a343eea0(iVar3,iVar2);
  lVar6 = thunk_EXT_FUN_7ff7a3180c53(&DAT_7ff7a3ccb21c);
  iVar2 = iVar3;
  if (((lVar6 != 0) && (iVar4 = FUN_7ff7a323fcb0(&DAT_7ff7a3ccb21c), iVar4 == 1)) &&
     (iVar2 = 1, iVar3 != 0)) {
    iVar2 = iVar3;
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar2;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

