// image offset 0x7897A0 address 7ff7a39197a0

int FUN_7ff7a39197a0(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = 0;
    plVar1 = &DAT_7ff7b0a3ced8;
    do {
      if (*plVar1 == param_1) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      plVar1 = plVar1 + 0xd;
    } while ((longlong)plVar1 < 0x7ff7b0a3cfa8);
  }
  return -1;
}

