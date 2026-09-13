// image offset 0x73F9F0 address 7ff7a38cf9f0

bool FUN_7ff7a38cf9f0(undefined4 param_1,undefined8 param_2,undefined4 param_3)

{
  int iVar1;
  undefined8 local_res20;

  FUN_7ff7a38f34d0("mp/unlocktable.csv",&local_res20);
  iVar1 = FUN_7ff7a38f3700(local_res20,0,param_2);
  if (iVar1 < 0) {
    return true;
  }
  iVar1 = thunk_EXT_FUN_7ff7a3180513(param_1,local_res20,iVar1,param_3);
  return iVar1 == 0;
}
