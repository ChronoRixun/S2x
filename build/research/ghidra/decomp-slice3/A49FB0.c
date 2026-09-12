// image offset 0xA49FB0 address 7ff7a3bd9fb0

undefined8 * FUN_7ff7a3bd9fb0(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df3460;
    param_1[3] = &DAT_7ff7a3df3468;
    param_1[0x6c] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 0x6d) = 0;
  }
  FUN_7ff7a3bd9f20(param_1,0);
  *param_1 = &PTR_FUN_7ff7a3df3438;
  param_1[2] = &PTR_FUN_7ff7a3df3448;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df3458;
  FUN_7ff7a3bda750(param_1);
  return param_1;
}

