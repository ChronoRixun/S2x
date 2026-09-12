// image offset 0x27D6B0 address 7ff7a340d6b0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a340d6b0(int param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  byte bVar4;
  longlong lVar5;
  longlong lVar6;
  short sVar7;
  undefined *puVar8;
  longlong lVar9;
  byte *pbVar10;
  undefined1 auStack_c8 [32];
  undefined1 local_a8 [8];
  longlong local_a0;
  longlong local_98;
  undefined1 local_88 [56];
  undefined1 local_50 [24];
  ulonglong local_38;
  
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_c8;
  lVar6 = (longlong)param_1;
  if ((((&DAT_7ff7ab32b568)[lVar6] != 0) &&
      (((DAT_7ff7ab0ff108 == 0 || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) &&
       (local_a0 = lVar6, cVar3 = FUN_7ff7a39caa20(param_1,local_a8), cVar3 != '\0')))) &&
     (lVar9 = lVar6 * 0xc8438, (&DAT_7ff7ab1c85a8)[lVar9] != '\0')) {
    lVar5 = FUN_7ff7a33981b0(5,param_1);
    local_98 = lVar5;
    cVar3 = FUN_7ff7a39c9650(lVar5);
    if ((cVar3 != '\0') && (cVar3 = FUN_7ff7a39c9710(lVar5), cVar3 != '\0')) {
      lVar6 = lVar6 * 0x16a0;
      puVar8 = &DAT_7ff7ab2dc330 + lVar6;
      FUN_7ff7a339d240(puVar8);
      FUN_7ff7a39c90a0(lVar6 + 0x7ff7ab2dd9b0);
      iVar1 = *(int *)(&DAT_7ff7ab1c85a4 + lVar9);
      sVar7 = 0;
      if (0 < iVar1) {
        do {
          pbVar10 = &DAT_7ff7ab1c6858 + lVar9 + sVar7;
          if ((*pbVar10 & 4) != 0) {
            lVar5 = (longlong)sVar7 * 0x68 + lVar9;
            iVar2 = *(int *)(&DAT_7ff7ab2dd9cc + lVar6);
            FUN_7ff7a3bbc490(local_88,local_a8,1);
            FUN_7ff7a3bbc740(puVar8 + (longlong)iVar2 * 0xc0 + 0x20,local_88);
            FUN_7ff7a3bbc6f0(local_50);
            FUN_7ff7a3c04d10(local_50);
            *(undefined4 *)(puVar8 + (longlong)iVar2 * 0xc0 + 0x68) =
                 *(undefined4 *)(&DAT_7ff7ab108178 + lVar5);
            *(undefined2 *)(puVar8 + (longlong)iVar2 * 0xc0 + 0xae) =
                 *(undefined2 *)(&DAT_7ff7ab108190 + lVar5);
            puVar8[(longlong)iVar2 * 0xc0 + 0xac] = (&DAT_7ff7ab1081d8)[lVar5];
            memcpy(puVar8 + (longlong)iVar2 * 0xc0 + 0x6c,&DAT_7ff7ab108198 + lVar5,
                   (ulonglong)(byte)(&DAT_7ff7ab1081d8)[lVar5]);
            bVar4 = *pbVar10;
            if ((bVar4 & 4) != 0) {
              bVar4 = bVar4 & 0xfb;
              *pbVar10 = bVar4;
              (&DAT_7ff7ab32b568)[local_a0] = (&DAT_7ff7ab32b568)[local_a0] + -1;
            }
            if ((bVar4 & 8) == 0) {
              *pbVar10 = bVar4 | 8;
            }
            *(int *)(&DAT_7ff7ab2dd9cc + lVar6) = *(int *)(&DAT_7ff7ab2dd9cc + lVar6) + 1;
            lVar5 = local_98;
            if (*(int *)(&DAT_7ff7ab2dd9cc + lVar6) == 0x1e) break;
          }
          sVar7 = sVar7 + 1;
          lVar5 = local_98;
        } while (sVar7 < iVar1);
      }
      FUN_7ff7a39c9700(lVar5,puVar8);
      *(code **)(lVar5 + 0x30) = thunk_FUN_7ff7b4ddd548;
      *(code **)(lVar5 + 0x40) = FUN_7ff7a340bcd0;
      *(code **)(lVar5 + 0x38) = FUN_7ff7a340bed0;
      FUN_7ff7a39c97e0(lVar5);
      return 1;
    }
  }
  return 0;
}

