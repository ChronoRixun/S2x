// image offset 0x333470 address 7ff7a34c3470

undefined8 FUN_7ff7a34c3470(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined8 uVar3;
  
  if ((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar3 = FUN_7ff7a360d050(0);
  iVar2 = FUN_7ff7a360e060(uVar3);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(iVar2 == 2);
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

