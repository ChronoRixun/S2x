// image offset 0xA70DE0 address 7ff7a3c00de0

undefined8 * FUN_7ff7a3c00de0(undefined8 *param_1,int param_2)

{
  if (param_2 != 0) {
    param_1[1] = &DAT_7ff7a3df4a08;
    param_1[0x392] = &PTR_FUN_7ff7a3ccfa28;
    *(undefined4 *)(param_1 + 0x393) = 0;
  }
  FUN_7ff7a3bcb420(param_1,0);
  *param_1 = &PTR_LAB_7ff7a3df49f0;
  *(undefined ***)((longlong)*(int *)(param_1[1] + 4) + 8 + (longlong)param_1) =
       &PTR_FUN_7ff7a3df4a00;
  FUN_7ff7a3c01010(param_1);
  return param_1;
}

