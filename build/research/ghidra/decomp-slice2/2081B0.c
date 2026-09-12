// image offset 0x2081B0 address 7ff7a33981b0

longlong FUN_7ff7a33981b0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  uint uVar4;
  
  lVar2 = FUN_7ff7a3398270(param_1);
  if (lVar2 == 0) {
    lVar2 = *(longlong *)(&DAT_7ff7aa102b00 + (longlong)param_1 * 8);
    if (((lVar2 == 0) || (*(int *)(&DAT_7ff7aa102b88 + (longlong)param_1 * 4) == 1)) ||
       (lVar3 = FUN_7ff7a3398270(param_1,param_2,param_3), lVar3 != 0)) {
      lVar2 = 0;
    }
    else {
      uVar4 = 0;
      do {
        lVar3 = (longlong)(int)uVar4 * 0x50 + lVar2;
        iVar1 = FUN_7ff7a39c9430(lVar3 + 8);
        if (iVar1 == 0) {
          *(undefined4 *)(lVar3 + 0x14) = param_3;
          *(undefined4 *)(lVar3 + 0xc) = param_2;
          return lVar3 + 8;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < 0x20);
      lVar2 = 0;
    }
  }
  return lVar2;
}

