// image offset 0xA4C310 address 7ff7a3bdc310

undefined8 * FUN_7ff7a3bdc310(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df3590;
    param_1[0x39] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 0x3a) = 0;
  }
  FUN_7ff7a3bcb420(param_1,0);
  *param_1 = &PTR_LAB_7ff7a3df3578;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df3588;
  FUN_7ff7a3bdc210(param_1 + 7,1);
  param_1[0x33] = 0;
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x38] = 0;
  FUN_7ff7a3bdcaf0(param_1);
  return param_1;
}

