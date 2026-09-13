// image offset 0xA77030 address 7ff7a3c07030

ulonglong FUN_7ff7a3c07030(undefined8 param_1,undefined4 *param_2)

{
  ulonglong uVar1;
  undefined4 local_res18 [4];
  
  uVar1 = FUN_7ff7a3c06a30(param_1,8);
  if ((char)uVar1 != '\0') {
    uVar1 = FUN_7ff7a3c06650(param_1,local_res18,4);
    if ((char)uVar1 != '\0') {
      *param_2 = local_res18[0];
      return CONCAT71((uint7)(uint3)((uint)local_res18[0] >> 8),1);
    }
  }
  return uVar1 & 0xffffffffffffff00;
}

