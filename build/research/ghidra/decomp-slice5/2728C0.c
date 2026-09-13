// image offset 0x2728C0 address 7ff7a34028c0

undefined1 FUN_7ff7a34028c0(longlong param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  
  if (param_1 != 0) {
    iVar3 = FUN_7ff7a3b94f40(param_1 + 0x90,"codpoints");
    if (iVar3 == 0) {
      return *(undefined1 *)(DAT_7ff7ad79ecc8 + 0x10);
    }
    iVar3 = *(int *)(param_1 + 0xb8);
    if ((iVar3 - 1U & 0xfffffffb) != 0) {
      if (iVar3 == 2) {
        uVar1 = FUN_7ff7a38f6160(7);
        return uVar1;
      }
      if (iVar3 == 3) {
        cVar2 = FUN_7ff7a38f6160(7);
        return cVar2 == '\0';
      }
      return true;
    }
  }
  return false;
}

