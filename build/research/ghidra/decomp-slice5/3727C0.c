// image offset 0x3727C0 address 7ff7a35027c0

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8
FUN_7ff7a35027c0(longlong param_1,undefined1 param_2,undefined8 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  undefined1 auStack_2fd8 [32];
  undefined4 local_2fb8;
  undefined8 local_2fa8;
  undefined8 local_2fa0;
  undefined1 local_2f98 [304];
  undefined1 local_2e68 [448];
  undefined1 local_2ca8 [304];
  undefined1 local_2b78 [384];
  undefined1 local_29f8 [384];
  undefined1 local_2878 [64];
  undefined1 local_2838 [2048];
  undefined1 local_2038 [4096];
  undefined1 local_1038 [4096];
  ulonglong local_38;
  undefined8 uStack_30;
  
  uStack_30 = 0x7ff7a35027d9;
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_2fd8;
  memcpy(local_1038,(void *)(param_1 + 0x2c),0x1000);
  local_2fb8 = 0x20;
  FUN_7ff7a340f8d0(local_2f98,local_1038,*(undefined4 *)(param_1 + 0x102c),local_2b78);
  iVar2 = FUN_7ff7a340ff40(local_2f98,&local_2fa8);
  if (-1 < iVar2) {
    memcpy(local_2838,(void *)(param_1 + 0x1030),0x800);
    local_2fb8 = 0x20;
    FUN_7ff7a340f8d0(local_2ca8,local_2838,*(undefined4 *)(param_1 + 0x1830),local_29f8);
    iVar2 = FUN_7ff7a340ff40(local_2ca8,&local_2fa0);
    if (-1 < iVar2) {
      FUN_7ff7a340f910(local_2e68,param_3,param_4,0);
      FUN_7ff7a3b94cd0(local_2878,0x40,&DAT_7ff7a3ccb22c,*(undefined8 *)(param_1 + 0x10));
      FUN_7ff7a340fe30(local_2e68,0);
      FUN_7ff7a34111f0(local_2e68,"messageID",local_2878);
      FUN_7ff7a340e9d0(local_2e68,"messageViewReported",param_2);
      for (lVar3 = FUN_7ff7a340efe0(local_2f98,local_2fa8); lVar3 != 0;
          lVar3 = FUN_7ff7a340f240(local_2f98,lVar3)) {
        uVar4 = FUN_7ff7a340f220(local_2f98);
        memset(local_2038,0,0x1000);
        iVar2 = FUN_7ff7a340f740(lVar3);
        if (iVar2 == 2) {
          uVar5 = FUN_7ff7a340f710(local_2f98,lVar3);
          local_2fb8 = 0x1000;
          FUN_7ff7a340e540(uVar5,local_2ca8,local_2fa0,local_2038);
          FUN_7ff7a34111f0(local_2e68,uVar4,local_2038);
        }
        else if (iVar2 == 3) {
          uVar6 = FUN_7ff7a340f020(local_2f98,lVar3);
          FUN_7ff7a340ec20(local_2e68,uVar4,uVar6);
        }
        else if (iVar2 == 4) {
          uVar5 = FUN_7ff7a340f7b0(local_2f98,lVar3);
          FUN_7ff7a3411420(local_2e68,uVar4,uVar5);
        }
        else if ((iVar2 == 5) || (iVar2 == 6)) {
          uVar1 = FUN_7ff7a340efc0(lVar3);
          FUN_7ff7a340e9d0(local_2e68,uVar4,uVar1);
        }
      }
      FUN_7ff7a340fed0(local_2e68);
      iVar2 = FUN_7ff7a3411110(local_2e68);
      if (-1 < iVar2) {
        return 1;
      }
    }
  }
  return 0;
}

