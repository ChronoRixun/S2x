// image offset 0x27C1D0 address 7ff7a340c1d0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_7ff7a340c1d0(undefined4 param_1,undefined8 param_2,undefined8 param_3,longlong param_4
                          ,uint param_5)

{
  char cVar1;
  short sVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined1 auStack_188 [32];
  undefined1 *local_168;
  undefined1 local_160;
  undefined1 local_158 [16];
  undefined1 local_148 [16];
  undefined1 local_138 [56];
  undefined1 local_100 [16];
  undefined4 local_f0;
  int local_ec;
  undefined1 local_e8 [64];
  undefined1 local_a8;
  undefined8 local_a0;
  undefined2 local_98;
  undefined4 local_94;
  undefined1 local_88 [16];
  undefined1 local_78 [32];
  ulonglong local_58;

  local_58 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_188;
  uVar7 = 0;
  for (lVar4 = FUN_7ff7a340efe0(param_2,param_3); lVar4 != 0;
      lVar4 = FUN_7ff7a340f240(param_2,lVar4)) {
    FUN_7ff7a3bd9140(local_158,1);
    for (lVar5 = FUN_7ff7a340efe0(param_2,lVar4); lVar5 != 0;
        lVar5 = FUN_7ff7a340f240(param_2,lVar5)) {
      uVar6 = FUN_7ff7a340f220(param_2,lVar5);
      iVar3 = FUN_7ff7a3b94f40(uVar6,"item_id");
      if (iVar3 == 0) {
        local_f0 = FUN_7ff7a340f750(param_2,lVar5);
      }
      else {
        iVar3 = FUN_7ff7a3b94f40(uVar6,"collision_field");
        if (iVar3 == 0) {
          local_98 = FUN_7ff7a340f750(param_2,lVar5);
        }
        else {
          iVar3 = FUN_7ff7a3b94f40(uVar6,"expiry_duration");
          if (iVar3 == 0) {
            cVar1 = FUN_7ff7a340fce0(lVar5);
            if (cVar1 == '\0') {
              local_a0 = FUN_7ff7a340f1e0(param_2,lVar5);
            }
          }
          else {
            iVar3 = FUN_7ff7a3b94f40(uVar6,"item_quantity");
            if (iVar3 == 0) {
              local_ec = FUN_7ff7a340f750(param_2,lVar5);
            }
            else {
              iVar3 = FUN_7ff7a3b94f40(uVar6,"mod_date_time");
              if (iVar3 == 0) {
                local_94 = FUN_7ff7a340f750(param_2,lVar5);
              }
            }
          }
        }
      }
    }
    if (local_ec == 0) {
      FUN_7ff7a340e0e0(param_1,local_f0);
    }
    else if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
      FUN_7ff7a339c850(local_78,local_158);
      local_160 = local_a8;
      local_168 = local_e8;
      sVar2 = FUN_7ff7a340dd30(param_1,local_78,0,1);
      if ((sVar2 != -1) && ((uint)uVar7 < param_5)) {
        *(int *)(uVar7 * 8 + 4 + param_4) = local_ec;
        *(undefined4 *)(uVar7 * 8 + param_4) = local_f0;
        uVar7 = (ulonglong)((uint)uVar7 + 1);
      }
    }
    FUN_7ff7a34052e0(param_1,2);
    FUN_7ff7a3bbc6f0(local_100);
    FUN_7ff7a3c04d10(local_100);
    FUN_7ff7a3bcb570(local_138);
    FUN_7ff7a3bbc060(local_148);
    FUN_7ff7a3c04d10(local_88);
  }
  return uVar7;
}
