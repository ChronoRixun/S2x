// image offset 0xA49F20 address 7ff7a3bd9f20

undefined8 * FUN_7ff7a3bd9f20(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df3428;
    param_1[3] = &DAT_7ff7a3df3430;
    param_1[0x6b] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  FUN_7ff7a3bd9e50(param_1,0);
  *param_1 = &PTR_FUN_7ff7a3df3400;
  param_1[2] = &PTR_FUN_7ff7a3df3410;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df3420;
  FUN_7ff7a3bda730(param_1);
  return param_1;
}

