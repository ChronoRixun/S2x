// image offset 0x274EC0 address 7ff7a3404ec0

int FUN_7ff7a3404ec0(int param_1,longlong param_2,int param_3)

{
  longlong lVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  
  iVar4 = 0;
  lVar1 = (longlong)param_1;
  iVar5 = 0;
  if ((int)(&DAT_7ff7ab0f6890)[lVar1 * 0x65] < 1) {
    return 0;
  }
  puVar3 = (undefined4 *)(&DAT_7ff7ab0f6894 + lVar1 * 0x194);
  lVar6 = 0;
  do {
    if (param_3 <= lVar6) {
      return iVar4;
    }
    if ((((DAT_7ff7ad79ecc8 != 0) && (*(char *)(DAT_7ff7ad79ecc8 + 0x10) != '\0')) ||
        (pcVar2 = (char *)FUN_7ff7a3261ba0(*puVar3,0x13), pcVar2 == (char *)0x0)) ||
       (*pcVar2 != '1')) {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(param_2 + lVar6 * 8) = *puVar3;
      *(undefined4 *)(param_2 + 4 + lVar6 * 8) = puVar3[1];
      lVar6 = lVar6 + 1;
    }
    iVar5 = iVar5 + 1;
    puVar3 = puVar3 + 2;
  } while (iVar5 < (int)(&DAT_7ff7ab0f6890)[lVar1 * 0x65]);
  return iVar4;
}

