// image offset 0x11EF30 address 7ff7a32aef30

undefined8 FUN_7ff7a32aef30(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  
  if (((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) !=
         2) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
      (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) ||
     (iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar3 = 0;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar5;
  }
  iVar4 = FUN_7ff7a325cb30(param_1,2);
  if (iVar4 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  cVar2 = FUN_7ff7a34066f0(iVar3,iVar4);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

