// image offset 0x123710 address 7ff7a32b3710

undefined8 FUN_7ff7a32b3710(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  
  bVar3 = 0;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar4 = FUN_7ff7a3468d90(param_1);
    if (iVar4 == 0) goto LAB_7ff7a32b3759;
    iVar4 = thunk_FUN_7ff7a3294bb0(param_1,2);
    if (iVar4 == 0) goto LAB_7ff7a32b3759;
  }
  else {
LAB_7ff7a32b3759:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar4 = (int)fVar6;
    if (iVar4 == -1) goto LAB_7ff7a32b379e;
  }
  else {
    iVar4 = 0;
  }
  cVar2 = FUN_7ff7a391a170(iVar4);
  if (cVar2 != '\0') {
    iVar4 = FUN_7ff7a3631610();
  }
LAB_7ff7a32b379e:
  iVar5 = FUN_7ff7a325cb30(param_1,2);
  if (iVar5 != 0) {
    bVar3 = FUN_7ff7a340a310(iVar4,iVar5);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

