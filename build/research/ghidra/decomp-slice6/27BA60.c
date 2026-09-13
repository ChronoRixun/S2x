// image offset 0x27BA60 address 7ff7a340ba60

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a340ba60(undefined8 param_1)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  uint uVar4;
  uint uVar5;
  longlong lVar6;
  undefined1 auStack_68 [32];
  longlong local_48;
  undefined1 local_40;
  undefined1 local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_68;
  iVar1 = FUN_7ff7a39c9370();
  lVar2 = FUN_7ff7a39c9390(param_1);
  uVar4 = 0;
  uVar5 = 0;
  if (*(int *)(lVar2 + 800) != 0) {
    do {
      lVar3 = (ulonglong)uVar5 * 0x80 + *(longlong *)(lVar2 + 0x328);
      FUN_7ff7a340dc10(iVar1,*(undefined1 *)(lVar3 + 0x68),*(undefined4 *)(lVar3 + 0x6c));
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(lVar2 + 800));
  }
  lVar3 = DAT_7ff7ab0ff108;
  if (*(int *)(lVar2 + 0x338) != 0) {
    do {
      lVar6 = (ulonglong)uVar4 * 0xe0 + *(longlong *)(lVar2 + 0x340);
      if ((lVar3 == 0) || (*(int *)(lVar3 + 0x10) != 0)) {
        FUN_7ff7a339c8b0(local_38,lVar6);
        local_40 = *(undefined1 *)(lVar6 + 0xb0);
        local_48 = lVar6 + 0x70;
        FUN_7ff7a340dd30(iVar1,local_38,0,1);
        FUN_7ff7a34052e0(iVar1,2);
        lVar3 = DAT_7ff7ab0ff108;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(lVar2 + 0x338));
  }
  FUN_7ff7a3265f30(iVar1);
  FUN_7ff7a3406220(&DAT_7ff7ab320ffc + (longlong)iVar1 * 0x2360);
  FUN_7ff7a34052e0(iVar1,2);
  return;
}

