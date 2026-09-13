// image offset 0x274570 address 7ff7a3404570

undefined8 FUN_7ff7a3404570(undefined4 param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  bool bVar9;
  undefined8 local_18;
  
  if (param_4 == 0x96) {
    FUN_7ff7a339d430(&local_18);
    pcVar6 = (char *)FUN_7ff7a3261ba0(param_2,0x2e);
    iVar3 = 0;
    if ((pcVar6 != (char *)0x0) && (iVar3 = 0, *pcVar6 != '\0')) {
      iVar3 = FUN_7ff7a3b94ed0(pcVar6);
    }
    bVar9 = false;
    pcVar6 = (char *)FUN_7ff7a3261ba0(param_2,0x2f);
    if ((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) {
      iVar4 = FUN_7ff7a3b94ed0(pcVar6);
      bVar9 = iVar4 == 1;
    }
    cVar2 = FUN_7ff7a3229040();
    if ((iVar3 != 0) && (((!bVar9 || (cVar2 != '\0')) && (DAT_7ff7ab0f4880 != '\0')))) {
      uVar5 = FUN_7ff7a3409410(param_2,0x800);
      uVar7 = (ulonglong)uVar5;
      sVar1 = (&DAT_7ff7a3f98840)[uVar7];
      while (sVar1 != -1) {
        if (*(int *)(&DAT_7ff7ab0f4890 + (longlong)sVar1 * 8) == param_2) {
          iVar3 = *(int *)(&DAT_7ff7ab0f4894 + (longlong)sVar1 * 8);
          uVar7 = 6;
          goto LAB_7ff7a3404661;
        }
        uVar7 = (ulonglong)((int)uVar7 + 1U & 0x7ff);
        sVar1 = (&DAT_7ff7a3f98840)[uVar7];
      }
    }
    uVar7 = local_18 & 0xffffffff;
    if ((int)local_18 != 0) {
      iVar3 = local_18._4_4_;
LAB_7ff7a3404661:
      uVar5 = FUN_7ff7a3409780(param_1,uVar7);
      if ((-1 < (int)uVar5) && ((uint)(iVar3 * param_3) <= uVar5)) {
        return 1;
      }
    }
  }
  else {
    uVar7 = 0;
    local_18 = 0;
    FUN_7ff7a34097e0(param_2,&local_18);
    if (local_18 != 0) {
      uVar8 = uVar7;
      if (*(char *)(local_18 + 0x2e1) != '\0') {
        do {
          uVar5 = FUN_7ff7a3409780(param_1,*(undefined4 *)(uVar8 + 0x24c + local_18));
          if ((int)uVar5 < 0) {
            return 0;
          }
          if (uVar5 < (uint)(param_3 * *(int *)(uVar8 + 0x250 + local_18))) {
            return 0;
          }
          uVar5 = (int)uVar7 + 1;
          uVar7 = (ulonglong)uVar5;
          uVar8 = uVar8 + 8;
        } while ((int)uVar5 < (int)(uint)*(byte *)(local_18 + 0x2e1));
      }
      return 1;
    }
  }
  return 0;
}

