// image offset 0x27E450 address 7ff7a340e450

void FUN_7ff7a340e450(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,
                     char param_5,char *param_6)

{
  int iVar1;
  undefined8 *puVar2;
  longlong lVar3;
  undefined1 *puVar4;
  int iVar5;
  longlong lVar6;
  
  lVar6 = (longlong)param_1;
  iVar1 = (&DAT_7ff7ab330570)[lVar6];
  iVar5 = iVar1;
  if (param_5 != '\0') {
    lVar3 = (longlong)(iVar1 + -1);
    if (-1 < iVar1 + -1) {
      puVar2 = (undefined8 *)(&DAT_7ff7ab32b598 + (lVar6 * 0x100 + lVar3) * 0x28);
      do {
        lVar3 = lVar3 + -1;
        *puVar2 = puVar2[-5];
        puVar2[1] = puVar2[-4];
        puVar2[2] = puVar2[-3];
        puVar2[3] = puVar2[-2];
        puVar2[4] = puVar2[-1];
        puVar2 = puVar2 + -5;
      } while (-1 < lVar3);
    }
    iVar5 = 0;
  }
  lVar3 = lVar6 * 0x100 + (longlong)iVar5;
  *(undefined4 *)(&DAT_7ff7ab32b590 + lVar3 * 0x28) = param_3;
  puVar4 = &DAT_7ff7ab32b574 + lVar3 * 0x28;
  *(undefined4 *)(&DAT_7ff7ab32b570 + lVar3 * 0x28) = param_2;
  iVar5 = 0x19;
  (&DAT_7ff7ab32b594)[lVar3 * 0x28] = param_4;
  if (*param_6 != '\0') {
    lVar3 = (longlong)param_6 - (longlong)puVar4;
    do {
      if (iVar5 < 2) break;
      iVar5 = iVar5 + -1;
      *puVar4 = puVar4[lVar3];
      puVar4 = puVar4 + 1;
    } while (puVar4[lVar3] != '\0');
  }
  *puVar4 = 0;
  (&DAT_7ff7ab330570)[lVar6] = iVar1 + 1;
  return;
}

