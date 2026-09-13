// image offset 0xA643D0 address 7ff7a3bf43d0

undefined8 FUN_7ff7a3bf43d0(longlong param_1,undefined8 param_2,longlong *param_3)

{
  int iVar1;
  ulonglong uVar2;
  char cVar3;
  uint uVar4;
  undefined8 uVar5;
  ulonglong local_res8;
  longlong local_res20;
  undefined1 local_38 [32];
  
  uVar4 = FUN_7ff7a3bf46e0(param_1,param_2,2);
  if (uVar4 == 0) {
    local_res8 = 0;
    cVar3 = FUN_7ff7a3c03bd0(param_1 + 0x10,&local_res8);
    uVar2 = local_res8;
    if (cVar3 == '\0') {
      *(undefined4 *)(param_1 + 0xc) = 2;
      return 0;
    }
    if (0xffffffff < local_res8) {
      FUN_7ff7a3c03e00(param_1 + 0x10,local_res8);
      *(undefined4 *)(param_1 + 0xc) = 4;
      return 0;
    }
    iVar1 = *(int *)(param_1 + 8);
    local_res20 = *(longlong *)(param_1 + 0x10);
    if (local_res20 != 0) {
      LOCK();
      *(int *)(local_res20 + 8) = *(int *)(local_res20 + 8) + 1;
      UNLOCK();
    }
    FUN_7ff7a3bf4080(local_38,&local_res20,local_res8 & 0xffffffff,iVar1 + 1);
    cVar3 = (**(code **)(*param_3 + 8))(param_3,local_38);
    if (cVar3 == '\0') {
      uVar4 = FUN_7ff7a3bf4150(local_38);
      if (uVar4 < 2) {
        uVar4 = 4;
      }
    }
    else {
      FUN_7ff7a3c039d0(param_1 + 0x10,uVar2 & 0xffffffff);
    }
    FUN_7ff7a3bf4120(local_38);
  }
  *(uint *)(param_1 + 0xc) = uVar4;
  if ((uVar4 == 0) || (uVar4 == 1)) {
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

