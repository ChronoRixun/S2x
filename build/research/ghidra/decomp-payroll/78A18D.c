// image offset 0x78A18D address 7ff7a391a18d

uint FUN_7ff7a391a180(longlong param_1)

{
  uint uVar1;
  longlong *plVar2;
  
  if (param_1 != 0) {
    uVar1 = 0;
    plVar2 = &DAT_7ff7b0a3ced8;
    do {
      if (*plVar2 == param_1) goto LAB_7ff7a391a1ad;
      uVar1 = uVar1 + 1;
      plVar2 = plVar2 + 0xd;
    } while ((longlong)plVar2 < 0x7ff7b0a3cfa8);
  }
  uVar1 = 0xffffffff;
LAB_7ff7a391a1ad:
  return uVar1 >> 0x1f ^ 1;
}

