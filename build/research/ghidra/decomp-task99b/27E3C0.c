// image offset 0x27E3C0 address 7ff7a340e3c0

ulonglong FUN_7ff7a340e3c0(int param_1)

{
  uint uVar1;
  ulonglong uVar2;
  int *piVar3;
  
  uVar2 = 0;
  piVar3 = &DAT_7ff7ab2938b0;
  do {
    if (param_1 == *piVar3) {
      if ((uVar2 * 0x2e8 != -0x7ff7ab2938b0) && ((&DAT_7ff7ab293af0)[uVar2 * 0xba] != 0)) {
        return CONCAT71((int7)(uVar2 >> 8),1);
      }
      break;
    }
    uVar1 = (int)uVar2 + 1;
    uVar2 = (ulonglong)uVar1;
    piVar3 = piVar3 + 0xba;
  } while (uVar1 < 400);
  return uVar2 & 0xffffffffffffff00;
}

