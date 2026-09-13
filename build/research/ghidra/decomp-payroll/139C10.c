// image offset 0x139C10 address 7ff7a32c9c10

undefined4 FUN_7ff7a32c9c10(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_1 != 0) {
    iVar1 = FUN_7ff7a3b94f40(param_1,"inactive");
    if (iVar1 == 0) {
      return 1;
    }
    iVar1 = FUN_7ff7a3b94f40(param_1,"inProgress");
    if (iVar1 == 0) {
      return 2;
    }
    iVar1 = FUN_7ff7a3b94f40(param_1,"claimable");
    if (iVar1 == 0) {
      return 3;
    }
    iVar1 = FUN_7ff7a3b94f40(param_1,"finished");
    uVar2 = 0;
    if (iVar1 == 0) {
      uVar2 = 4;
    }
  }
  return uVar2;
}

