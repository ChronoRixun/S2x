// image offset 0xA485A0 address 7ff7a3bd85a0

undefined8 * FUN_7ff7a3bd85a0(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df32c0;
    param_1[3] = &DAT_7ff7a3df32c8;
    param_1[5] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 6) = 0;
  }
  FUN_7ff7a3bbc030(param_1,0);
  FUN_7ff7a3bcb540(param_1 + 2,0);
  *param_1 = &PTR_FUN_7ff7a3df3298;
  param_1[2] = &PTR_FUN_7ff7a3df32a8;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df32b8;
  FUN_7ff7a3bd8770(param_1);
  return param_1;
}

