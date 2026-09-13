// image offset 0x278FB0 address 7ff7a3408fb0

ulonglong FUN_7ff7a3408fb0(int param_1,longlong param_2)

{
  ulonglong uVar1;
  ulonglong uVar2;
  int *piVar3;
  uint uVar4;
  ulonglong uVar5;
  
  if ((DAT_7ff7ab2938ac == param_1) && (DAT_7ff7ab2938a8 != '\0')) {
    uVar1 = 0;
    piVar3 = &DAT_7ff7ab2938b0;
    uVar2 = uVar1;
    uVar5 = uVar1;
    do {
      if (*piVar3 != 0) {
        *(int *)(param_2 + uVar2 * 4) = *piVar3;
        uVar1 = (ulonglong)((int)uVar1 + 1);
        uVar2 = uVar2 + 1;
        if (uVar2 == 400) {
          return uVar1;
        }
      }
      uVar4 = (int)uVar5 + 1;
      uVar5 = (ulonglong)uVar4;
      piVar3 = piVar3 + 0xba;
    } while (uVar4 < 400);
    return uVar1;
  }
  return 0;
}

