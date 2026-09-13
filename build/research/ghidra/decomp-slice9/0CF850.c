// image offset 0xCF850 address 7ff7a325f850

int FUN_7ff7a325f850(int param_1,int param_2,undefined8 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  char *pcVar6;
  undefined8 local_res18;
  undefined8 local_res20;
  ulonglong in_stack_ffffffffffffff58;
  undefined8 local_88;
  undefined8 local_80;
  undefined1 local_78 [48];
  undefined1 local_48 [48];

  if ((param_1 != -1) && (cVar1 = FUN_7ff7a391a170(), cVar1 != '\0')) {
    param_1 = FUN_7ff7a3631610();
  }
  FUN_7ff7a38f34d0("mp/unlocktable.csv",&local_res18);
  if (param_2 != 0) {
    FUN_7ff7a38f34d0("mp/statstable.csv",&local_res20);
    uVar5 = FUN_7ff7a37e2610(param_2);
    param_3 = FUN_7ff7a38f3560(local_res20,0x12,uVar5);
  }
  iVar2 = FUN_7ff7a38f3700(local_res18,0,param_3);
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  else {
    uVar3 = FUN_7ff7a325f390(param_1);
    in_stack_ffffffffffffff58 = in_stack_ffffffffffffff58 & 0xffffffffffffff00;
    cVar1 = FUN_7ff7a331dcf0(local_48,param_1,uVar3,4,in_stack_ffffffffffffff58);
    if (cVar1 == '\0') {
      iVar2 = 0x13;
    }
    else {
      uVar3 = FUN_7ff7a325f390(param_1);
      cVar1 = FUN_7ff7a331dcf0(local_78,param_1,uVar3,0,
                               in_stack_ffffffffffffff58 & 0xffffffffffffff00);
      if (cVar1 == '\0') {
        iVar2 = 0x13;
      }
      else {
        iVar2 = thunk_EXT_FUN_7ff7a3180553(param_2,param_1,local_48,local_78,local_res18,iVar2,0);
        if (iVar2 == 0x10) {
          return 0x10;
        }
      }
    }
  }
  if (param_2 != 0) {
    FUN_7ff7a38f34d0("mp/statstable.csv",&local_res18);
    uVar5 = FUN_7ff7a37e2610(param_2);
    pcVar6 = (char *)FUN_7ff7a38f3560(local_res18,0x12,uVar5);
    if ((pcVar6 == (char *)0x0) || (iVar4 = atoi(pcVar6), iVar4 != 1)) {
      FUN_7ff7a38f34d0("mp/statstable.csv",&local_res20);
      uVar5 = FUN_7ff7a37e2610(param_2);
      pcVar6 = (char *)FUN_7ff7a38f3560(local_res20,0x12,uVar5);
      if ((pcVar6 == (char *)0x0) || (iVar4 = atoi(pcVar6), iVar4 != 1)) {
        FUN_7ff7a38f34d0("mp/statstable.csv",&local_88);
        uVar5 = FUN_7ff7a37e2610(param_2);
        pcVar6 = (char *)FUN_7ff7a38f3560(local_88,0x12,uVar5);
        if ((pcVar6 == (char *)0x0) || (iVar4 = atoi(pcVar6), iVar4 != 1)) {
          FUN_7ff7a38f34d0("mp/statstable.csv",&local_80);
          uVar5 = FUN_7ff7a37e2610(param_2);
          pcVar6 = (char *)FUN_7ff7a38f3560(local_80,0x12,uVar5);
          if (pcVar6 == (char *)0x0) {
            return iVar2;
          }
          iVar4 = atoi(pcVar6);
          if (iVar4 != 1) {
            return iVar2;
          }
        }
      }
    }
    cVar1 = FUN_7ff7a340a310(param_1,param_2);
    if (cVar1 == '\0') {
      return 0x11;
    }
  }
  return iVar2;
}
