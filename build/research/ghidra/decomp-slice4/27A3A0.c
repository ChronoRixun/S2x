// image offset 0x27A3A0 address 7ff7a340a3a0

void FUN_7ff7a340a3a0(int param_1,short param_2,int param_3,char param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  
  lVar5 = (longlong)param_1 * 0xc8438;
  uVar3 = param_3 >> 0x1f & 7;
  param_3 = param_3 + uVar3;
  lVar4 = (longlong)param_2 * 0x68 + lVar5;
  lVar6 = (longlong)(param_3 >> 3);
  bVar2 = '\x01' << (((byte)param_3 & 7) - (char)uVar3 & 0x1f);
  if ((((&DAT_7ff7ab108198)[lVar4 + lVar6] & bVar2) != 0) != (bool)param_4) {
    bVar1 = (&DAT_7ff7ab108198)[lVar6 + lVar4];
    if (param_4 == '\0') {
      bVar1 = bVar1 & ~bVar2;
    }
    else {
      bVar1 = bVar1 | bVar2;
    }
    (&DAT_7ff7ab108198)[lVar6 + lVar4] = bVar1;
    (&DAT_7ff7ab1081d8)[lVar4] = 0x40;
    bVar2 = (&DAT_7ff7ab1c6858)[lVar5 + param_2];
    if ((bVar2 & 4) == 0) {
      (&DAT_7ff7ab32b568)[param_1] = (&DAT_7ff7ab32b568)[param_1] + 1;
      (&DAT_7ff7ab1c6858)[lVar5 + param_2] = bVar2 | 4;
    }
  }
  return;
}

