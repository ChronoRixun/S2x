// image offset 0x279300 address 7ff7a3409300

short FUN_7ff7a3409300(int param_1,int param_2,undefined8 *param_3)

{
  short sVar1;
  int iVar2;
  char *pcVar3;
  longlong lVar4;
  ulonglong uVar5;
  uint uVar6;
  longlong lVar8;
  char cVar9;
  ulonglong uVar7;
  
  uVar5 = 0;
  uVar6 = 0;
  lVar8 = (longlong)param_1 * 0xc8438;
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = 0;
  }
  pcVar3 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4);
  if ((pcVar3 != (char *)0x0) && (cVar9 = *pcVar3, cVar9 != '\0')) {
    lVar4 = -1;
    do {
      lVar4 = lVar4 + 1;
    } while (pcVar3[lVar4] != '\0');
    lVar4 = (longlong)((int)lVar4 + 1);
    uVar7 = uVar5;
    do {
      uVar6 = (uint)uVar7;
      if ((lVar4 != 0) && (lVar4 <= (longlong)uVar5)) break;
      uVar5 = uVar5 + 1;
      iVar2 = (int)cVar9;
      cVar9 = pcVar3[uVar5];
      uVar6 = uVar6 * 0x1f + iVar2;
      uVar7 = (ulonglong)uVar6;
    } while (cVar9 != '\0');
  }
  uVar5 = (ulonglong)(uVar6 & 0x1fff);
  sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar5 * 2 + lVar8);
  while( true ) {
    if (sVar1 == 0) {
      return -1;
    }
    sVar1 = *(short *)(&DAT_7ff7ab100178 + uVar5 * 2 + lVar8);
    if (param_2 == *(int *)(&DAT_7ff7ab108178 + (longlong)sVar1 * 0x68 + lVar8)) break;
    uVar6 = (int)uVar5 + 1U & 0x1fff;
    uVar5 = (ulonglong)uVar6;
    sVar1 = *(short *)(&DAT_7ff7ab104178 + (ulonglong)uVar6 * 2 + lVar8);
  }
  if (param_3 == (undefined8 *)0x0) {
    return sVar1;
  }
  *param_3 = &DAT_7ff7ab108178 + (longlong)sVar1 * 0x68 + lVar8;
  return sVar1;
}

