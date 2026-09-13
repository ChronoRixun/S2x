// image offset 0x120870 address 7ff7a32b0870

undefined8 FUN_7ff7a32b0870(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  float fVar4;
  undefined4 local_res8 [2];
  
  if (((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) !=
         2) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
      (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) ||
     (iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar3 = 0;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar4 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar4;
  }
  local_res8[0] = FUN_7ff7a325cb30(param_1,2);
  cVar2 = FUN_7ff7a34088e0(iVar3,local_res8,1);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

