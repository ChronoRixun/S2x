// image offset 0x27EFE0 address 7ff7a340efe0

longlong FUN_7ff7a340efe0(longlong param_1,uint *param_2)

{
  uint uVar1;
  
  if (((*param_2 & 0xe0000000) < 0x40000000) && (uVar1 = *param_2 & 0x1fffffff, uVar1 != 0x1fffffff)
     ) {
    return *(longlong *)(param_1 + 0x118) + (ulonglong)uVar1 * 0xc;
  }
  return 0;
}

