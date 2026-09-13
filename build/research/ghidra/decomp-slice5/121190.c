// image offset 0x121190 address 7ff7a32b1190

undefined8 FUN_7ff7a32b1190(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  
  uVar4 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar4 == 1) {
    iVar2 = thunk_FUN_7ff7a3294bb0(param_1,uVar4 & 0xffffffff);
    if (iVar2 != 0) goto LAB_7ff7a32b11c8;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b11c8:
  iVar3 = 0;
  iVar2 = FUN_7ff7a325cb30(param_1,1);
  if (iVar2 != 0) {
    iVar3 = FUN_7ff7a3404c00(iVar2);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar3;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

