// image offset 0xA64650 address 7ff7a3bf4650

undefined4 FUN_7ff7a3bf4650(longlong param_1,undefined8 param_2,undefined4 *param_3)

{
  int iVar1;
  ulonglong local_res8;
  
  iVar1 = FUN_7ff7a3bf4240(param_1,param_2,&local_res8);
  if (iVar1 == 0) {
    if (0xffffffff < local_res8) {
      FUN_7ff7a3c0e4a0();
      *(undefined4 *)(param_1 + 0xc) = 4;
      return 0;
    }
    *param_3 = (int)local_res8;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  else {
    *(int *)(param_1 + 0xc) = iVar1;
    if (iVar1 != 1) {
      return 0;
    }
  }
  return 1;
}

