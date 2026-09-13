// image offset 0x27F220 address 7ff7a340f220

longlong FUN_7ff7a340f220(longlong param_1,longlong param_2)

{
  if (*(uint *)(param_2 + 4) == 0xffffffff) {
    return 0;
  }
  return (ulonglong)*(uint *)(param_2 + 4) + *(longlong *)(param_1 + 0x100);
}

