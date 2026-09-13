// image offset 0x27A4C0 address 7ff7a340a4c0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a340a4c0(undefined8 param_1)

{
  short sVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  uint uVar6;
  undefined1 auStack_78 [32];
  longlong local_58;
  undefined1 local_50;
  undefined1 local_48 [32];
  ulonglong local_28;
  
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_78;
  uVar2 = FUN_7ff7a39c9370();
  lVar3 = FUN_7ff7a39c9390(param_1);
  uVar6 = 0;
  uVar5 = 0;
  if (*(int *)(lVar3 + 0x22c) != 0) {
    do {
      lVar4 = (ulonglong)uVar5 * 0xf0 + *(longlong *)(lVar3 + 0x220);
      if (*(int *)(lVar4 + 0x7c) == 0) {
        FUN_7ff7a340e0e0(uVar2,*(undefined4 *)(lVar4 + 0x78));
      }
      else if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
        FUN_7ff7a339c880(local_48,lVar4);
        local_50 = *(undefined1 *)(lVar4 + 0xc4);
        local_58 = lVar4 + 0x84;
        sVar1 = FUN_7ff7a340dd30(uVar2,local_48,0,1);
        if (sVar1 != -1) {
          FUN_7ff7a34052e0(uVar2,2);
        }
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(lVar3 + 0x22c));
  }
  if (*(int *)(lVar3 + 0x21c) != 0) {
    do {
      lVar4 = (ulonglong)uVar6 * 0x98 + *(longlong *)(lVar3 + 0x210);
      FUN_7ff7a340d510(uVar2,*(undefined4 *)(lVar4 + 0x78),*(undefined4 *)(lVar4 + 0x7c));
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(lVar3 + 0x21c));
  }
  FUN_7ff7a3265f30(uVar2);
  FUN_7ff7a3405570(uVar2,lVar3 + 0x4c,0);
  FUN_7ff7a3405360(uVar2,0x7e,1,lVar3 + 0x4c);
  FUN_7ff7a34052e0(uVar2,2);
  return;
}

