// image offset 0x279480 address 7ff7a3409480

undefined4 FUN_7ff7a3409480(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  longlong local_res18 [2];
  
  cVar1 = thunk_EXT_FUN_7ff7a31804d4(param_2);
  if (cVar1 != '\0') {
    return 1;
  }
  uVar2 = 0;
  local_res18[0] = 0;
  FUN_7ff7a3409300(param_1,param_2,local_res18);
  if (local_res18[0] != 0) {
    uVar2 = *(undefined4 *)(local_res18[0] + 4);
  }
  return uVar2;
}

