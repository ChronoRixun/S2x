// image offset 0x27A3A0 address 7ff7a340a3a0

void FUN_7ff7a340a3a0(int param_1,short param_2,int param_3,char param_4)

{
  int *piVar1;
  byte bVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  
  lVar7 = (longlong)param_1 * 0xc8438;
  uVar5 = param_3 >> 0x1f & 7;
  param_3 = param_3 + uVar5;
  lVar6 = (longlong)param_2 * 0x68 + lVar7;
  lVar8 = (longlong)(param_3 >> 3);
  bVar4 = '\x01' << (((byte)param_3 & 7) - (char)uVar5 & 0x1f);
  if (((*(byte *)(lVar6 + lVar8 + 0x7ff7ab108198) & bVar4) != 0) != (bool)param_4) {
    bVar2 = *(byte *)(lVar6 + 0x7ff7ab108198 + lVar8);
    if (param_4 == '\0') {
      bVar2 = bVar2 & ~bVar4;
    }
    else {
      bVar2 = bVar2 | bVar4;
    }
    *(byte *)(lVar6 + 0x7ff7ab108198 + lVar8) = bVar2;
    *(undefined1 *)(lVar6 + 0x7ff7ab1081d8) = 0x40;
    pbVar3 = (byte *)(lVar7 + param_2 + 0x7ff7ab1c6858);
    bVar4 = *pbVar3;
    if ((bVar4 & 4) == 0) {
      piVar1 = (int *)((longlong)param_1 * 4 + 0x7ff7ab32b568);
      *piVar1 = *piVar1 + 1;
      *pbVar3 = bVar4 | 4;
    }
  }
  return;
}

