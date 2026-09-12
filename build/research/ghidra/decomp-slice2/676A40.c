// image offset 0x676A40 address 7ff7a3806a40

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a3806a40(undefined4 param_1,undefined8 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  undefined4 *puVar6;
  longlong lVar7;
  ulonglong uVar8;
  undefined1 auStack_61d8 [32];
  undefined4 local_61b8;
  undefined8 local_61a8;
  undefined8 local_61a0;
  undefined4 local_6198 [2];
  undefined8 local_6190;
  undefined8 local_6188 [2];
  undefined1 local_6178 [304];
  undefined1 local_6048 [24576];
  ulonglong local_48;

  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_61d8;
  lVar5 = FUN_7ff7a3bcb850(param_2);
  lVar7 = -1;
  do {
    lVar7 = lVar7 + 1;
  } while (*(char *)(lVar5 + lVar7) != '\0');
  local_61b8 = 0x800;
  FUN_7ff7a340f8d0(local_6178,lVar5,lVar7,local_6048);
  iVar3 = FUN_7ff7a340ff40(local_6178,&local_61a8);
  if ((((-1 < iVar3) &&
       (cVar2 = FUN_7ff7a340f570(local_6178,local_61a8,"Action",&local_61a0), cVar2 != '\0')) &&
      (cVar2 = FUN_7ff7a340f570(local_6178,local_61a8,"Status",local_6188), cVar2 != '\0')) &&
     ((cVar2 = FUN_7ff7a340f570(local_6178,local_61a8,"ClientTx",&local_6190), cVar2 != '\0' &&
      (uVar4 = FUN_7ff7a3806860(local_61a0,local_6198,2), uVar4 != 0)))) {
    puVar6 = local_6198;
    uVar8 = (ulonglong)uVar4;
    do {
      uVar1 = *puVar6;
      lVar5 = FUN_7ff7a3398270(param_3,param_1,uVar1);
      if ((lVar5 != 0) && (lVar7 = FUN_7ff7a39c9390(lVar5), lVar7 != 0)) {
        lVar7 = lVar7 + 0xd0;
        iVar3 = FUN_7ff7a3b94f90(lVar7,local_6190);
        if (iVar3 == 0) {
          iVar3 = FUN_7ff7a3b94f90(local_6188[0],&DAT_7ff7a3d28054);
          if (iVar3 == 0) {
            *(undefined1 *)(lVar5 + 2) = 0;
            switch(uVar1) {
            case 0x16:
              FUN_7ff7a32ca330(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x2c:
              FUN_7ff7a343f950(param_1,local_6178,local_61a8);
              break;
            case 0x30:
              FUN_7ff7a343f3a0(param_1,local_6178,local_61a8);
              break;
            case 0x72:
              FUN_7ff7a32cec20(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x7f:
              FUN_7ff7a343f7a0(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x82:
              FUN_7ff7a343f200(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x84:
              FUN_7ff7a32ce960(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x85:
              FUN_7ff7a32cf190(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x8d:
            case 0x99:
              FUN_7ff7a32ce8b0(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x8e:
              FUN_7ff7a32ce950(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x8f:
              FUN_7ff7a32cef20(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0x9e:
              FUN_7ff7a32ce910(param_1,local_6178,local_61a8,lVar7);
              break;
            case 0xa0:
              FUN_7ff7a32d25c0(param_1,local_6178,local_61a8,lVar7);
            }
          }
          else {
            FUN_7ff7a39c9970(lVar5);
          }
        }
      }
      puVar6 = puVar6 + 1;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  return;
}
