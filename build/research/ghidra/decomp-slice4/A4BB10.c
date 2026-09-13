// image offset 0xA4BB10 address 7ff7a3bdbb10

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool FUN_7ff7a3bdbb10(undefined8 param_1,undefined4 param_2,longlong *param_3)

{
  uint uVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  uint uVar6;
  longlong lVar7;
  char cVar8;
  longlong lVar9;
  longlong lVar10;
  ulonglong uVar11;
  longlong lVar12;
  uint uVar13;
  undefined1 auStack_138 [32];
  char local_118;
  undefined4 local_114;
  undefined8 local_110;
  longlong local_108;
  longlong local_100;
  longlong local_f8;
  undefined1 local_e8 [16];
  undefined1 local_d8 [56];
  undefined1 local_a0 [16];
  undefined1 local_90 [48];
  undefined1 local_60 [24];
  ulonglong local_48;
  
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_138;
  bVar2 = true;
  local_114 = param_2;
  local_110 = param_1;
  FUN_7ff7a3bdc910(param_3,*param_3,*(undefined4 *)((longlong)param_3 + 0xc));
  FUN_7ff7a3c05240(*param_3);
  *param_3 = 0;
  param_3[1] = 0;
  cVar8 = '\0';
  local_118 = '\0';
  do {
    if (cVar8 != '\0') {
      return bVar2;
    }
    FUN_7ff7a3bfd5c0(local_e8,1);
    if ((bVar2) && (cVar3 = FUN_7ff7a3bf43d0(param_1,param_2,local_e8), cVar3 != '\0')) {
      bVar2 = true;
      iVar4 = FUN_7ff7a3bf4150(param_1);
      if (iVar4 == 1) {
        cVar8 = '\x01';
        local_118 = '\x01';
      }
      else {
        uVar6 = *(uint *)((longlong)param_3 + 0xc);
        uVar1 = *(uint *)(param_3 + 1);
        if (uVar6 == uVar1) {
          uVar13 = uVar1;
          if (uVar1 == 0) {
            uVar13 = 1;
          }
          lVar5 = 0;
          uVar13 = uVar13 + uVar1;
          if (uVar13 != 0) {
            lVar5 = FUN_7ff7a3c05210((ulonglong)uVar13 * 0x98);
            lVar10 = *param_3;
            uVar6 = 0;
            if (*(uint *)((longlong)param_3 + 0xc) != 0) {
              uVar11 = (ulonglong)*(uint *)((longlong)param_3 + 0xc);
              lVar9 = lVar5;
              do {
                local_108 = lVar9;
                local_100 = lVar9;
                if (lVar9 != 0) {
                  FUN_7ff7a3bfd4c0(lVar9,(lVar10 - lVar5) + lVar9,1);
                }
                lVar9 = lVar9 + 0x98;
                uVar11 = uVar11 - 1;
              } while (uVar11 != 0);
              uVar6 = *(uint *)((longlong)param_3 + 0xc);
            }
          }
          lVar10 = *param_3;
          if (uVar6 != 0) {
            lVar12 = 0;
            lVar9 = 0;
            uVar11 = (ulonglong)uVar6;
            do {
              lVar7 = (longlong)*(int *)(*(longlong *)(lVar10 + 8 + lVar12) + 4);
              (*(code *)**(undefined8 **)(lVar7 + lVar12 + 8 + lVar10))
                        (lVar10 + 8 + lVar7 + lVar9,0);
              lVar9 = lVar9 + 0x98;
              lVar12 = lVar12 + 0x98;
              uVar11 = uVar11 - 1;
            } while (uVar11 != 0);
            lVar10 = *param_3;
            param_2 = local_114;
          }
          FUN_7ff7a3c05240(lVar10);
          *param_3 = lVar5;
          *(uint *)(param_3 + 1) = uVar13;
          param_1 = local_110;
          cVar8 = local_118;
        }
        else {
          lVar5 = *param_3;
        }
        uVar6 = *(uint *)((longlong)param_3 + 0xc);
        local_108 = (ulonglong)uVar6 * 0x98 + lVar5;
        local_f8 = local_108;
        if (local_108 != 0) {
          FUN_7ff7a3bfd4c0(local_108,local_e8,1);
          uVar6 = *(uint *)((longlong)param_3 + 0xc);
        }
        *(uint *)((longlong)param_3 + 0xc) = uVar6 + 1;
      }
    }
    else {
      bVar2 = false;
    }
    FUN_7ff7a3bcb470(local_90);
    FUN_7ff7a3bbc6f0(local_a0);
    FUN_7ff7a3c04d10(local_90);
    FUN_7ff7a3bcb470(local_d8);
    FUN_7ff7a3c04d10(local_60);
  } while (bVar2 != false);
  return false;
}

