// image offset 0x3111D0 address 7ff7a34a11d0

undefined8 FUN_7ff7a34a11d0(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  float fVar6;
  
  uVar4 = *(ulonglong *)(param_1 + 0x48);
  uVar5 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar4 - uVar5) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar5 = *(ulonglong *)(param_1 + 0x50);
    uVar4 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar5 < uVar4) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 != 0) goto LAB_7ff7a34a1227;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a34a1227:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
  }
  else {
    fVar6 = 0.0;
  }
  cVar2 = FUN_7ff7a39d0df0((int)fVar6);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

