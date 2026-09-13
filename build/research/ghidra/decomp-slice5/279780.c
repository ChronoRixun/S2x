// image offset 0x279780 address 7ff7a3409780

undefined4 FUN_7ff7a3409780(int param_1,uint param_2)

{
  uint uVar1;
  ulonglong uVar2;
  byte *pbVar3;
  longlong lVar4;
  
  lVar4 = (longlong)param_1 * 0x2e0;
  if ((&DAT_7ff7ab0ffe94)[lVar4] != '\0') {
    uVar2 = 0;
    pbVar3 = &DAT_7ff7ab0ffbd8 + lVar4;
    do {
      if (*pbVar3 == param_2) {
        lVar4 = uVar2 * 0x38 + lVar4;
        if (lVar4 == -0x7ff7ab0ffbb8) {
          return 0;
        }
        return *(undefined4 *)(&DAT_7ff7ab0ffbdc + lVar4);
      }
      uVar1 = (int)uVar2 + 1;
      uVar2 = (ulonglong)uVar1;
      pbVar3 = pbVar3 + 0x38;
    } while (uVar1 < 0xd);
  }
  return 0;
}

