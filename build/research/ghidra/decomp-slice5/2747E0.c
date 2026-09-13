// image offset 0x2747E0 address 7ff7a34047e0

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int FUN_7ff7a34047e0(undefined4 param_1,longlong param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  char *_Str;
  undefined4 *puVar6;
  longlong lVar7;
  longlong lVar8;
  undefined4 *puVar9;
  longlong lVar10;
  int iVar11;
  int iVar12;
  undefined1 auStack_1348 [32];
  int local_1328;
  int local_1324;
  int local_1320;
  undefined4 local_131c;
  longlong local_1318;
  undefined4 local_1308 [1200];
  ulonglong local_48;
  
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1348;
  local_1328 = param_4;
  local_131c = param_1;
  local_1318 = param_2;
  cVar4 = FUN_7ff7a340a1f0();
  if (cVar4 == '\0') {
    iVar12 = 0;
  }
  else {
    iVar11 = 0;
    iVar12 = 0;
    lVar8 = 0;
    iVar5 = 0;
    do {
      if (lVar8 == param_3) {
        return iVar12;
      }
      local_1324 = FUN_7ff7a34094f0(param_1,local_1308,300,iVar5);
      local_1320 = iVar5 + local_1324;
      lVar7 = 0;
      lVar10 = (longlong)local_1324;
      if (0 < local_1324) {
        puVar9 = local_1308;
        puVar6 = (undefined4 *)(lVar8 * 0x10 + local_1318);
        do {
          _Str = (char *)FUN_7ff7a3261ba0(*puVar9,0x16);
          if ((_Str != (char *)0x0) && (iVar5 = atoi(_Str), 0 < iVar5)) {
            uVar1 = puVar9[1];
            uVar2 = puVar9[2];
            uVar3 = puVar9[3];
            *puVar6 = *puVar9;
            puVar6[1] = uVar1;
            puVar6[2] = uVar2;
            puVar6[3] = uVar3;
            if (iVar11 < local_1328) {
              iVar11 = iVar11 + 1;
            }
            else {
              iVar12 = iVar12 + 1;
              lVar8 = lVar8 + 1;
              puVar6 = puVar6 + 4;
              if (lVar8 == param_3) break;
            }
          }
          lVar7 = lVar7 + 1;
          puVar9 = puVar9 + 4;
        } while (lVar7 < lVar10);
      }
      iVar5 = local_1320;
      param_1 = local_131c;
    } while (local_1324 == 300);
  }
  return iVar12;
}

