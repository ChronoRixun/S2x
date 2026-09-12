// image offset 0x3722A0 address 7ff7a35022a0

void FUN_7ff7a3502200(int param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong lVar7;
  
  lVar7 = (longlong)param_1;
  lVar5 = lVar7 * 0x110;
  plVar6 = (longlong *)(&DAT_7ff7abba4f60 + lVar5);
  if (*(int *)(DAT_7ff7ad79e9c0 + 0x10) != 0) {
    pcVar3 = (char *)FUN_7ff7a33981b0(4,param_1);
    cVar1 = FUN_7ff7a3919cc0(param_1);
    if (((cVar1 == '\0') || (cVar1 = FUN_7ff7a391a170(param_1), cVar1 != '\0')) || (*pcVar3 != '\0')
       ) {
      (&DAT_7ff7abba4f84)[lVar7 * 0x44] = 0;
    }
    else {
      if (((&DAT_7ff7abba4f84)[lVar7 * 0x44] != 0) &&
         (iVar2 = FUN_7ff7a3941290(),
         *(int *)(DAT_7ff7ad79e9c8 + 0x10) * 1000 < iVar2 - *(int *)(&DAT_7ff7abba4f8c + lVar5))) {
        (&DAT_7ff7abba4f84)[lVar7 * 0x44] = 0;
      }
      lVar4 = FUN_7ff7a3919870(param_1);
      if (*plVar6 != lVar4) {
        *(undefined8 *)(&DAT_7ff7abba4f88 + lVar5) = 1;
      }
      cVar1 = FUN_7ff7a3919d20(param_1);
      if ((cVar1 != '\0') && (((&DAT_7ff7abba4f84)[lVar7 * 0x44] == 0 || (*plVar6 != lVar4)))) {
        FUN_7ff7a3502cd0(param_1);
        *plVar6 = lVar4;
        FUN_7ff7a3502490(param_1);
      }
    }
  }
  FUN_7ff7a3398790(4);
  return;
}

