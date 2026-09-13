// image offset 0x27CA90 address 7ff7a340ca90

void FUN_7ff7a340ca90(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  longlong lVar3;
  uint uVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  char cVar8;
  
  lVar6 = (longlong)param_1 * 0xc8438;
  pcVar2 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4);
  uVar5 = 0;
  uVar4 = 0;
  if ((pcVar2 != (char *)0x0) && (cVar8 = *pcVar2, cVar8 != '\0')) {
    lVar3 = -1;
    do {
      lVar3 = lVar3 + 1;
    } while (pcVar2[lVar3] != '\0');
    lVar3 = (longlong)((int)lVar3 + 1);
    uVar7 = uVar5;
    do {
      uVar4 = (uint)uVar5;
      if ((lVar3 != 0) && (lVar3 <= (longlong)uVar7)) break;
      uVar7 = uVar7 + 1;
      iVar1 = (int)cVar8;
      cVar8 = pcVar2[uVar7];
      uVar4 = uVar4 * 0x1f + iVar1;
      uVar5 = (ulonglong)uVar4;
    } while (cVar8 != '\0');
  }
  uVar5 = (ulonglong)(uVar4 & 0x1fff);
  if (*(short *)(&DAT_7ff7ab104178 + uVar5 * 2 + lVar6) != 0) {
    while( true ) {
      if (param_2 ==
          *(int *)(&DAT_7ff7ab108178 +
                  (longlong)*(short *)(&DAT_7ff7ab100178 + uVar5 * 2 + lVar6) * 0x68 + lVar6))
      break;
      uVar4 = (int)uVar5 + 1U & 0x1fff;
      uVar5 = (ulonglong)uVar4;
      if (*(short *)(&DAT_7ff7ab104178 + (ulonglong)uVar4 * 2 + lVar6) == 0) {
        return;
      }
    }
    if ((int *)(&DAT_7ff7ab108178 +
               (longlong)*(short *)(&DAT_7ff7ab100178 + uVar5 * 2 + lVar6) * 0x68 + lVar6) !=
        (int *)0x0) {
      FUN_7ff7a340a3a0(param_1,*(short *)(&DAT_7ff7ab100178 + uVar5 * 2 + lVar6),1,1);
    }
  }
  return;
}

