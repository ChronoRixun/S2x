// image offset 0x274B90 address 7ff7a3404b90

undefined * FUN_7ff7a3404b90(undefined8 param_1,int param_2)

{
  longlong lVar1;
  longlong *plVar2;
  uint uVar3;
  
  lVar1 = FUN_7ff7a3919870();
  if (lVar1 != 0) {
    uVar3 = 0;
    plVar2 = &DAT_7ff7ab0f41b8;
    do {
      if (*plVar2 == lVar1) {
        if (&DAT_7ff7ab0f3ba0 + (longlong)(int)uVar3 * 0x620 == (undefined *)0x0) {
          return (undefined *)0x0;
        }
        return &DAT_7ff7ab0f3ba0 + (longlong)(int)uVar3 * 0x620 + (longlong)param_2 * 0x208;
      }
      uVar3 = uVar3 + 1;
      plVar2 = plVar2 + 0xc4;
    } while (uVar3 < 2);
  }
  return (undefined *)0x0;
}

