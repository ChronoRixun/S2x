// image offset 0xA50B00 address 7ff7a3be0b00

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool FUN_7ff7a3be0a60(longlong param_1,undefined8 param_2)

{
  bool bVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  void *_Dst;
  uint uVar6;
  undefined1 auStack_1d08 [32];
  undefined1 local_1ce8 [16];
  undefined1 local_1cd8 [7296];
  undefined1 local_58 [16];
  ulonglong local_48;
  undefined8 uStack_40;
  
  uStack_40 = 0x7ff7a3be0a7a;
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1d08;
  FUN_7ff7a3c05240(*(undefined8 *)(param_1 + 0x10));
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  bVar1 = true;
  FUN_7ff7a3c05240(0);
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  bVar3 = false;
  do {
    if (bVar3) {
      return bVar1;
    }
    FUN_7ff7a3c00de0(local_1ce8,1);
    if ((bVar1) && (cVar4 = FUN_7ff7a3bf43d0(param_2,1,local_1ce8), cVar4 != '\0')) {
      bVar1 = true;
      iVar5 = FUN_7ff7a3bf4150(param_2);
      if (iVar5 == 1) {
        bVar3 = true;
      }
      else {
        iVar5 = *(int *)(param_1 + 0x18);
        if (*(int *)(param_1 + 0x1c) == iVar5) {
          iVar2 = iVar5;
          if (iVar5 == 0) {
            iVar2 = 1;
          }
          uVar6 = iVar2 + iVar5;
          _Dst = (void *)0x0;
          if (uVar6 != 0) {
            _Dst = (void *)FUN_7ff7a3c05210((ulonglong)uVar6 * 0x1ca0);
            if (*(uint *)(param_1 + 0x1c) != 0) {
              memcpy(_Dst,*(void **)(param_1 + 0x10),(ulonglong)*(uint *)(param_1 + 0x1c) * 0x1ca0);
            }
          }
          FUN_7ff7a3c05240(*(undefined8 *)(param_1 + 0x10));
          *(void **)(param_1 + 0x10) = _Dst;
          *(uint *)(param_1 + 0x18) = uVar6;
        }
        else {
          _Dst = *(void **)(param_1 + 0x10);
        }
        memcpy((void *)((ulonglong)*(uint *)(param_1 + 0x1c) * 0x1ca0 + (longlong)_Dst),local_1ce8,
               0x1ca0);
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
      }
    }
    else {
      bVar1 = false;
    }
    FUN_7ff7a3bcb470(local_1cd8);
    FUN_7ff7a3c04d10(local_58);
  } while (bVar1 != false);
  return false;
}

