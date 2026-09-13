// image offset 0x274970 address 7ff7a3404970

undefined8 FUN_7ff7a3404970(int param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  ulonglong uVar7;
  bool bVar8;
  undefined4 local_res10;
  undefined4 uStackX_14;
  
  FUN_7ff7a339d430(&local_res10);
  pcVar6 = (char *)FUN_7ff7a3261ba0(param_1,0x2e);
  iVar3 = 0;
  if ((pcVar6 != (char *)0x0) && (iVar3 = 0, *pcVar6 != '\0')) {
    iVar3 = FUN_7ff7a3b94ed0(pcVar6);
  }
  bVar8 = false;
  pcVar6 = (char *)FUN_7ff7a3261ba0(param_1,0x2f);
  if ((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) {
    iVar4 = FUN_7ff7a3b94ed0(pcVar6);
    bVar8 = iVar4 == 1;
  }
  cVar2 = FUN_7ff7a3229040();
  if ((iVar3 != 0) && (((!bVar8 || (cVar2 != '\0')) && (DAT_7ff7ab0f4880 != '\0')))) {
    uVar5 = FUN_7ff7a3409410(param_1,0x800);
    uVar7 = (ulonglong)uVar5;
    sVar1 = (&DAT_7ff7a3f98840)[uVar7];
    while (sVar1 != -1) {
      if (*(int *)(&DAT_7ff7ab0f4890 + (longlong)sVar1 * 8) == param_1) {
        uStackX_14 = *(undefined4 *)(&DAT_7ff7ab0f4894 + (longlong)sVar1 * 8);
        local_res10 = 6;
        break;
      }
      uVar7 = (ulonglong)((int)uVar7 + 1U & 0x7ff);
      sVar1 = (&DAT_7ff7a3f98840)[uVar7];
    }
  }
  return CONCAT44(uStackX_14,local_res10);
}

