// image offset 0x27F240 address 7ff7a340f240

longlong FUN_7ff7a340f240(longlong param_1,longlong param_2)

{
  if (*(uint *)(param_2 + 8) == 0xffffffff) {
    return 0;
  }
  return *(longlong *)(param_1 + 0x118) + (ulonglong)*(uint *)(param_2 + 8) * 0xc;
}

