// image offset 0x120E50 address 7ff7a32b0e50

undefined8 FUN_7ff7a32b0e50(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  int iVar6;
  float fVar7;
  
  if (((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) !=
         2) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
      (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) ||
     ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U ||
      (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)))) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  iVar6 = 0;
  uVar5 = *(ulonglong *)(param_1 + 0x48);
  iVar3 = iVar6;
  if (uVar4 < uVar5) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1,uVar4);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar5 = *(ulonglong *)(param_1 + 0x48);
    iVar3 = (int)fVar7;
  }
  if (uVar4 + 0x10 < uVar5) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    iVar6 = (int)fVar7;
  }
  cVar2 = FUN_7ff7a3405110(iVar3,iVar6);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

