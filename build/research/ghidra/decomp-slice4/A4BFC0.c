// image offset 0xA4BFC0 address 7ff7a3bdbfc0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool FUN_7ff7a3bdbfc0(undefined8 param_1,undefined4 param_2,longlong *param_3)

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
  undefined1 auStack_188 [32];
  char local_168;
  undefined4 local_164;
  undefined8 local_160;
  longlong local_158;
  longlong local_150;
  longlong local_148;
  undefined1 local_138 [16];
  undefined1 local_128 [56];
  undefined1 local_f0 [16];
  undefined1 local_e0 [136];
  undefined1 local_58 [16];
  ulonglong local_48;
  
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_188;
  bVar2 = true;
  local_164 = param_2;
  local_160 = param_1;
  FUN_7ff7a3bdca10(param_3,*param_3,*(undefined4 *)((longlong)param_3 + 0xc));
  FUN_7ff7a3c05240(*param_3);
  *param_3 = 0;
  param_3[1] = 0;
  cVar8 = '\0';
  local_168 = '\0';
  do {
    if (cVar8 != '\0') {
      return bVar2;
    }
    FUN_7ff7a3bfd940(local_138,1);
    if ((bVar2) && (cVar3 = FUN_7ff7a3bf43d0(param_1,param_2,local_138), cVar3 != '\0')) {
      bVar2 = true;
      iVar4 = FUN_7ff7a3bf4150(param_1);
      if (iVar4 == 1) {
        cVar8 = '\x01';
        local_168 = '\x01';
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
            lVar5 = FUN_7ff7a3c05210((ulonglong)uVar13 * 0xf0);
            lVar10 = *param_3;
            uVar6 = 0;
            if (*(uint *)((longlong)param_3 + 0xc) != 0) {
              uVar11 = (ulonglong)*(uint *)((longlong)param_3 + 0xc);
              lVar9 = lVar5;
              do {
                local_158 = lVar9;
                local_150 = lVar9;
                if (lVar9 != 0) {
                  FUN_7ff7a3bfd7c0(lVar9,(lVar10 - lVar5) + lVar9,1);
                }
                lVar9 = lVar9 + 0xf0;
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
              lVar9 = lVar9 + 0xf0;
              lVar12 = lVar12 + 0xf0;
              uVar11 = uVar11 - 1;
            } while (uVar11 != 0);
            lVar10 = *param_3;
            param_2 = local_164;
          }
          FUN_7ff7a3c05240(lVar10);
          *param_3 = lVar5;
          *(uint *)(param_3 + 1) = uVar13;
          param_1 = local_160;
          cVar8 = local_168;
        }
        else {
          lVar5 = *param_3;
        }
        uVar6 = *(uint *)((longlong)param_3 + 0xc);
        local_158 = (ulonglong)uVar6 * 0xf0 + lVar5;
        local_148 = local_158;
        if (local_158 != 0) {
          FUN_7ff7a3bfd7c0(local_158,local_138,1);
          uVar6 = *(uint *)((longlong)param_3 + 0xc);
        }
        *(uint *)((longlong)param_3 + 0xc) = uVar6 + 1;
      }
    }
    else {
      bVar2 = false;
    }
    FUN_7ff7a3bcb470(local_e0);
    FUN_7ff7a3bbc6f0(local_f0);
    FUN_7ff7a3c04d10(local_e0);
    FUN_7ff7a3bcb470(local_128);
    FUN_7ff7a3c04d10(local_58);
  } while (bVar2 != false);
  return false;
}

