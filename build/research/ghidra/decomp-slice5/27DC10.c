// image offset 0x27DC10 address 7ff7a340dc10

int FUN_7ff7a340dc10(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  char *pcVar5;
  longlong lVar6;
  byte *pbVar7;
  longlong lVar8;
  
  lVar8 = (longlong)param_1 * 0x2e0;
  if ((&DAT_7ff7ab0ffe94)[lVar8] != '\0') {
    uVar3 = 0;
    pbVar7 = &DAT_7ff7ab0ffbd8 + lVar8;
    do {
      if (*pbVar7 == param_2) {
        lVar6 = (ulonglong)uVar3 * 0x38 + lVar8;
        if (lVar6 != -0x7ff7ab0ffbb8) {
          iVar1 = *(int *)(&DAT_7ff7ab0ffbdc + lVar6);
          if (iVar1 == param_3) {
            return 0;
          }
          *(int *)(&DAT_7ff7ab0ffbdc + lVar6) = param_3;
          param_3 = param_3 - iVar1;
          goto LAB_7ff7a340dcd3;
        }
        break;
      }
      uVar3 = uVar3 + 1;
      pbVar7 = pbVar7 + 0x38;
    } while (uVar3 < 0xd);
  }
  uVar3 = 0;
  pcVar5 = &DAT_7ff7ab0ffbd8 + lVar8;
  while (*pcVar5 != '\0') {
    uVar3 = uVar3 + 1;
    pcVar5 = pcVar5 + 0x38;
    if (0xc < uVar3) {
      return 0;
    }
  }
  if (uVar3 == 0xffffffff) {
    return 0;
  }
  lVar6 = (longlong)(int)uVar3 * 0x38 + lVar8;
  (&DAT_7ff7ab0ffbd8)[lVar6] = (char)param_2;
  *(int *)(&DAT_7ff7ab0ffbdc + lVar6) = param_3;
  *(int *)(&DAT_7ff7ab0ffe90 + lVar8) = *(int *)(&DAT_7ff7ab0ffe90 + lVar8) + 1;
LAB_7ff7a340dcd3:
  if ((param_2 == 1) && (uVar3 != 0xffffffff)) {
    uVar2 = *(undefined4 *)(&DAT_7ff7ab0ffbdc + (longlong)(int)uVar3 * 0x38 + lVar8);
    uVar4 = FUN_7ff7a3819900(DAT_7ff7ad7912d4);
    FUN_7ff7a331e9e0(param_1,uVar4,uVar2,0);
    return param_3;
  }
  return param_3;
}

