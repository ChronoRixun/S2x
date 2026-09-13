// image offset 0xA4CC30 address 7ff7a3bdcc30

undefined8 * FUN_7ff7a3bdcc30(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df35f8;
    param_1[3] = &DAT_7ff7a3df3600;
    param_1[7] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  FUN_7ff7a3bdccc0(param_1,0);
  *param_1 = &PTR_FUN_7ff7a3df35d0;
  param_1[2] = &PTR_FUN_7ff7a3df35e0;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df35f0;
  *(undefined2 *)(param_1 + 6) = 0;
  return param_1;
}

