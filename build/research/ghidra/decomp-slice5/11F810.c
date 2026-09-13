// image offset 0x11F810 address 7ff7a32af810

undefined8 FUN_7ff7a32af810(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  
  uVar5 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar5 == 1) {
    iVar3 = thunk_FUN_7ff7a3294bb0(param_1,uVar5 & 0xffffffff);
    if (iVar3 != 0) goto LAB_7ff7a32af844;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af844:
  uVar4 = FUN_7ff7a325cb30(param_1,1);
  cVar2 = thunk_EXT_FUN_7ff7a31804d4(uVar4);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

