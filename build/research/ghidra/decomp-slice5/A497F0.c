// image offset 0xA497F0 address 7ff7a3bd97f0

undefined8 * FUN_7ff7a3bd97f0(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df3378;
    param_1[3] = &DAT_7ff7a3df3380;
    param_1[5] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 6) = 0;
  }
  FUN_7ff7a3bbc030(param_1,0);
  FUN_7ff7a3bcb540(param_1 + 2,0);
  *param_1 = &PTR_FUN_7ff7a3df3350;
  param_1[2] = &PTR_FUN_7ff7a3df3360;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df3370;
  FUN_7ff7a3bd9980(param_1);
  return param_1;
}

