// image offset 0x279010 address 7ff7a3409010

int FUN_7ff7a3409010(int param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  char *pcVar3;
  ulonglong uVar4;
  int iVar5;
  longlong lVar6;
  int *piVar7;
  longlong lVar8;
  longlong lVar9;
  char cVar10;
  
  lVar8 = (longlong)param_1 * 0xc8438;
  pcVar3 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4);
  uVar2 = 0;
  if (pcVar3 != (char *)0x0) {
    cVar10 = *pcVar3;
    uVar2 = 0;
    if (cVar10 != '\0') {
      lVar6 = -1;
      do {
        lVar6 = lVar6 + 1;
      } while (pcVar3[lVar6] != '\0');
      lVar9 = (longlong)((int)lVar6 + 1);
      lVar6 = 0;
      do {
        if ((lVar9 != 0) && (lVar9 <= lVar6)) break;
        lVar6 = lVar6 + 1;
        iVar5 = (int)cVar10;
        cVar10 = pcVar3[lVar6];
        uVar2 = uVar2 * 0x1f + iVar5;
      } while (cVar10 != '\0');
    }
  }
  uVar2 = uVar2 & 0x1fff;
  uVar4 = (ulonglong)uVar2;
  sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar4 * 2 + lVar8);
  while( true ) {
    if (sVar1 == 0) {
      return 0;
    }
    piVar7 = (int *)(&DAT_7ff7ab108178 +
                    (longlong)*(short *)(&DAT_7ff7ab100178 + (ulonglong)uVar2 * 2 + lVar8) * 0x68 +
                    lVar8);
    if (param_2 == *piVar7) break;
    uVar2 = (int)uVar4 + 1U & 0x1fff;
    uVar4 = (ulonglong)uVar2;
    sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar4 * 2 + lVar8);
  }
  if (piVar7 == (int *)0x0) {
    return 0;
  }
  return piVar7[2];
}

