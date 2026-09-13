// image offset 0x278180 address 7ff7a3408180

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_7ff7a3408180(int param_1,char *param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  char cVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  int iVar8;
  longlong lVar9;
  uint uVar10;
  longlong lVar11;
  undefined1 *puVar12;
  uint uVar13;
  int iVar14;
  longlong lVar15;
  undefined1 auStack_a8 [32];
  undefined4 *local_88;
  undefined4 local_78 [2];
  undefined1 local_70 [24];
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined4 local_38;
  undefined1 local_34;
  ulonglong local_30;
  
  local_30 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_a8;
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    uVar10 = 0;
    _DAT_7ff7ab330690 = 0;
    uRam00007ff7ab330698 = 0;
    local_58 = 0;
    uStack_50 = 0;
    local_48 = 0;
    uStack_40 = 0;
    local_38 = 0;
    local_34 = 0;
    FUN_7ff7a3c07a10(local_70);
    iVar14 = 0x10;
    local_78[0] = 0x10;
    lVar15 = -1;
    do {
      lVar15 = lVar15 + 1;
    } while (param_2[lVar15] != '\0');
    local_88 = local_78;
    puVar12 = &DAT_7ff7ab330690;
    FUN_7ff7a3c07ce0(local_70,param_2,lVar15,&DAT_7ff7ab330690);
    uVar7 = FUN_7ff7a38fd940(_DAT_7ff7ab330690 & 0xffffffff);
    uVar3 = _DAT_7ff7ab330690;
    _DAT_7ff7ab330690 = CONCAT44(_DAT_7ff7ab330694,uVar7);
    uVar4 = _DAT_7ff7ab330690;
    DAT_7ff7ab330694 = SUB82(uVar3,4);
    uVar6 = DAT_7ff7ab330694;
    _DAT_7ff7ab330690 = uVar4;
    uVar6 = FUN_7ff7a38fd980(uVar6);
    _DAT_7ff7ab330690 = CONCAT24(uVar6,_DAT_7ff7ab330690);
    uVar6 = FUN_7ff7a38fd980(DAT_7ff7ab330696);
    _DAT_7ff7ab330690 = CONCAT26(uVar6,_DAT_7ff7ab330690);
    uVar13 = 0;
    do {
      iVar8 = FUN_7ff7a3b94cd0((longlong)&local_58 + (ulonglong)uVar10,0x25 - (ulonglong)uVar10,
                               &DAT_7ff7a3cdeaac,*puVar12);
      uVar10 = uVar10 + iVar8;
      if ((uVar13 - 3 & 0xfffffff9) == 0) {
        iVar8 = FUN_7ff7a3b94cd0((longlong)&local_58 + (ulonglong)uVar10,0x25 - (ulonglong)uVar10,
                                 &DAT_7ff7a3cdeab4);
        uVar10 = uVar10 + iVar8;
      }
      uVar13 = uVar13 + 1;
      puVar12 = puVar12 + 1;
    } while (uVar13 < 0x10);
    FUN_7ff7a3c07b40(local_70);
    if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
      lVar15 = FUN_7ff7a33981b0(5,param_1);
      cVar5 = FUN_7ff7a39c9650(lVar15);
      if ((cVar5 != '\0') && (cVar5 = FUN_7ff7a39c9710(lVar15), cVar5 != '\0')) {
        lVar11 = (longlong)param_1 * 0x250;
        FUN_7ff7a339cb80(&DAT_7ff7ab326038 + lVar11);
        puVar12 = &DAT_7ff7ab326048 + lVar11;
        lVar9 = (longlong)"s2_steam" - (longlong)puVar12;
        do {
          if (iVar14 < 2) break;
          *puVar12 = puVar12[lVar9];
          iVar14 = iVar14 + -1;
          puVar12 = puVar12 + 1;
        } while (puVar12[lVar9] != '\0');
        *puVar12 = 0;
        *(undefined8 *)(&DAT_7ff7ab326058 + lVar11) = local_58;
        *(undefined8 *)(lVar11 + 0x7ff7ab326060) = uStack_50;
        *(undefined8 *)(&DAT_7ff7ab326068 + lVar11) = local_48;
        *(undefined8 *)(lVar11 + 0x7ff7ab326070) = uStack_40;
        *(undefined4 *)(&DAT_7ff7ab326078 + lVar11) = local_38;
        (&DAT_7ff7ab32607c)[lVar11] = local_34;
        *(undefined4 *)(&DAT_7ff7ab326080 + lVar11) = param_4;
        uVar7 = param_3[1];
        uVar1 = param_3[2];
        uVar2 = param_3[3];
        *(undefined4 *)(&DAT_7ff7ab326084 + lVar11) = *param_3;
        *(undefined4 *)(lVar11 + 0x7ff7ab326088) = uVar7;
        *(undefined4 *)(lVar11 + 0x7ff7ab32608c) = uVar1;
        *(undefined4 *)(lVar11 + 0x7ff7ab326090) = uVar2;
        *(undefined8 *)(&DAT_7ff7ab326094 + lVar11) = *(undefined8 *)(param_3 + 4);
        (&DAT_7ff7ab32609c)[lVar11] = *(undefined1 *)(param_3 + 6);
        FUN_7ff7a39c9700(lVar15,&DAT_7ff7ab326038 + lVar11);
        *(code **)(lVar15 + 0x30) = thunk_FUN_7ff7b51a2152;
        *(code **)(lVar15 + 0x40) = FUN_7ff7a340a460;
        *(code **)(lVar15 + 0x38) = FUN_7ff7a340a4c0;
        FUN_7ff7a39c97e0(lVar15);
        return 1;
      }
    }
  }
  return 0;
}

