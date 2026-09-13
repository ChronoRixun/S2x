// image offset 0xA646C0 address 7ff7a3bf46c0

bool FUN_7ff7a3bf46c0(longlong param_1)

{
  uint uVar1;
  
  uVar1 = FUN_7ff7a3bf4240();
  *(uint *)(param_1 + 0xc) = uVar1;
  return uVar1 < 2;
}

