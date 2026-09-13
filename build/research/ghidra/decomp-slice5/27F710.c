// image offset 0x27F710 address 7ff7a340f710

longlong FUN_7ff7a340f710(longlong param_1,uint *param_2)

{
  uint uVar1;
  
  if (((*param_2 & 0xe0000000) == 0x40000000) &&
     (uVar1 = *param_2 & 0x1fffffff, uVar1 != 0x1fffffff)) {
    return (ulonglong)uVar1 + *(longlong *)(param_1 + 0x100);
  }
  return 0;
}

