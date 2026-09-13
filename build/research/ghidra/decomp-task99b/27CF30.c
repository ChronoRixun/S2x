// image offset 0x27CF30 address 7ff7a340cf30

/* WARNING: Removing unreachable block (ram,0x7ff7a340d076) */
/* WARNING: Removing unreachable block (ram,0x7ff7a340d080) */
/* WARNING: Removing unreachable block (ram,0x7ff7a340d085) */

void FUN_7ff7a340cf30(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  char cVar3;
  short sVar4;
  int iVar5;
  longlong lVar6;
  undefined4 *puVar7;
  int iVar8;
  ulonglong uVar9;
  bool bVar10;
  
  uVar9 = (ulonglong)param_1;
  if ((((DAT_7ff7ab0ff108 != 0) && (*(int *)(DAT_7ff7ab0ff108 + 0x10) == 0)) ||
      (((&DAT_7ff7ab0ffe94)[uVar9 * 0x2e0] != '\0' && ((&DAT_7ff7ab1c85a8)[uVar9 * 0xc8438] != '\0')
       ))) && ((cVar3 = FUN_7ff7a38f6630(), cVar3 != '\0' &&
               (cVar3 = FUN_7ff7a376fa90(), iVar2 = DAT_7ff7a3f99878, cVar3 != '\0')))) {
    iVar8 = (&DAT_7ff7ab330570)[uVar9];
    bVar10 = false;
    if (iVar8 == 0) {
      if (1 < uVar9) {
                    /* WARNING: Subroutine does not return */
        FUN_7ff7a3c46630();
      }
      iVar8 = 0;
      (&DAT_7ff7ab330580)[uVar9] = 0;
      if (0 < iVar2) {
        puVar7 = &DAT_7ff7a3f99848;
        do {
          uVar1 = *puVar7;
          iVar2 = puVar7[1];
          cVar3 = FUN_7ff7a39c0070(uVar1);
          if (((cVar3 != '\0') && (iVar2 != 0)) &&
             (sVar4 = FUN_7ff7a3409300(param_1,iVar2,0), sVar4 == -1)) {
            iVar2 = (&DAT_7ff7ab330570)[uVar9];
            lVar6 = uVar9 * 0x100 + (longlong)iVar2;
            *(undefined4 *)(&DAT_7ff7ab32b570 + lVar6 * 0x28) = uVar1;
            *(undefined4 *)(&DAT_7ff7ab32b590 + lVar6 * 0x28) = 0;
            (&DAT_7ff7ab32b594)[lVar6 * 0x28] = 0;
            (&DAT_7ff7ab32b574)[lVar6 * 0x28] = 0;
            (&DAT_7ff7ab330570)[uVar9] = iVar2 + 1;
          }
          iVar8 = iVar8 + 1;
          puVar7 = puVar7 + 2;
        } while (iVar8 < DAT_7ff7a3f99878);
      }
      iVar8 = (&DAT_7ff7ab330570)[uVar9];
      bVar10 = iVar8 == 0;
    }
    if (!bVar10 && -1 < iVar8) {
      if (((&DAT_7ff7ab330578)[uVar9] == -1) && (DAT_7ff7ab0ff120 != 0)) {
        lVar6 = DAT_7ff7ab0ff120;
        iVar8 = FUN_7ff7a340e400(param_1);
        iVar2 = *(int *)(lVar6 + 0x10);
        iVar5 = FUN_7ff7a3941290();
        (&DAT_7ff7ab330578)[uVar9] = iVar8 * iVar2 + iVar5;
      }
      FUN_7ff7a340cbc0(param_1);
      return;
    }
    lVar6 = FUN_7ff7a3398270(5,param_1);
    if (lVar6 != 0) {
      *(undefined4 *)(lVar6 + 8) = 7;
    }
  }
  return;
}

