// image offset 0x274E80 address 7ff7a3404e80

undefined * FUN_7ff7a3404e80(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  uVar2 = 0;
  plVar1 = &DAT_7ff7ab0f41b8;
  do {
    if (*plVar1 == param_1) {
      return &DAT_7ff7ab0f3ba0 + (longlong)(int)uVar2 * 0x620;
    }
    uVar2 = uVar2 + 1;
    plVar1 = plVar1 + 0xc4;
  } while (uVar2 < 2);
  return (undefined *)0x0;
}

