// image offset 0x2AF560 address 7ff7a343f560

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a343f560(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  ulonglong uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined4 *puVar11;
  ulonglong uVar12;
  undefined8 *puVar13;
  longlong lVar14;
  undefined1 auStack_698 [32];
  undefined1 local_678 [64];
  int local_638 [28];
  undefined4 local_5c8 [100];
  undefined1 local_438 [1024];
  ulonglong local_38;
  
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_698;
  iVar3 = FUN_7ff7a36321d0(param_1);
  cVar2 = FUN_7ff7a3248c40();
  if ((cVar2 != '\0') && (8 < (int)(&DAT_7ff7a4d3f4e4)[(longlong)iVar3 * 0x1ee])) {
    uVar4 = 0;
    lVar14 = (longlong)param_1 * 0x154;
    cVar2 = FUN_7ff7a39c9000(&DAT_7ff7ab973b30 + lVar14,&DAT_7ff7ab973b30 + lVar14);
    uVar12 = uVar4;
    uVar9 = uVar4;
    if (cVar2 != '\0') {
      if (*(int *)(&DAT_7ff7ab973c14 + lVar14) != 0) {
        uVar8 = uVar4;
        uVar10 = uVar4;
        do {
          uVar1 = *(undefined4 *)(&DAT_7ff7ab973b4c + (uVar10 + (longlong)param_1 * 0x55) * 4);
          cVar2 = FUN_7ff7a3405230(uVar1);
          uVar9 = uVar8;
          if ((cVar2 == '\0') && (cVar2 = FUN_7ff7a3406bc0(uVar1), cVar2 == '\0')) {
            uVar7 = (int)uVar8 + 1;
            uVar9 = (ulonglong)uVar7;
            local_5c8[uVar8 * 2 + 1] = 1;
            local_5c8[uVar8 * 2] = uVar1;
            if (0x31 < uVar7) break;
          }
          uVar7 = (int)uVar10 + 1;
          uVar10 = (ulonglong)uVar7;
          uVar8 = uVar9;
        } while (uVar7 < *(uint *)(&DAT_7ff7ab973c14 + lVar14));
      }
      uVar7 = *(uint *)(&DAT_7ff7ab973c80 + lVar14);
      if (uVar7 != 0) {
        puVar13 = (undefined8 *)(&DAT_7ff7ab973c18 + lVar14);
        do {
          *(undefined8 *)(local_638 + uVar12 * 2) = *puVar13;
          uVar5 = (int)uVar12 + 1;
          uVar12 = (ulonglong)uVar5;
          if (0xc < uVar5) break;
          uVar5 = (int)uVar4 + 1;
          uVar4 = (ulonglong)uVar5;
          puVar13 = puVar13 + 1;
        } while (uVar5 < uVar7);
      }
    }
    FUN_7ff7a326c720(local_678,local_438,0x3fc);
    FUN_7ff7a326dad0(local_678,99);
    FUN_7ff7a326dad0(local_678,uVar9);
    if ((int)uVar9 != 0) {
      puVar11 = local_5c8;
      do {
        FUN_7ff7a326dd60(local_678,*puVar11);
        puVar11 = puVar11 + 2;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
    }
    FUN_7ff7a326dad0(local_678,uVar12);
    if ((int)uVar12 != 0) {
      piVar6 = local_638 + 1;
      do {
        FUN_7ff7a326dad0(local_678,(longlong)piVar6[-1]);
        FUN_7ff7a326dd60(local_678,*piVar6);
        piVar6 = piVar6 + 2;
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
    }
    FUN_7ff7a31f0740(iVar3,local_678);
  }
  return;
}

