// image offset 0x2797E0 address 7ff7a34097e0

ulonglong FUN_7ff7a34097e0(int param_1,undefined8 *param_2)

{
  uint uVar1;
  ulonglong uVar2;
  int *piVar3;
  
  uVar2 = 0;
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
  }
  piVar3 = &DAT_7ff7ab2938b0;
  do {
    if (param_1 == *piVar3) {
      if (param_2 != (undefined8 *)0x0) {
        *param_2 = &DAT_7ff7ab2938b0 + uVar2 * 0xba;
      }
      return uVar2;
    }
    uVar1 = (int)uVar2 + 1;
    uVar2 = (ulonglong)uVar1;
    piVar3 = piVar3 + 0xba;
  } while (uVar1 < 400);
  return 0xffffffff;
}

