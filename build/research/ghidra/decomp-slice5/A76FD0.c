// image offset 0xA76FD0 address 7ff7a3c06fd0

ulonglong FUN_7ff7a3c06fd0(undefined8 param_1,undefined2 *param_2)

{
  ulonglong uVar1;
  undefined2 local_res18 [8];
  
  uVar1 = FUN_7ff7a3c06a30(param_1,6);
  if ((char)uVar1 != '\0') {
    uVar1 = FUN_7ff7a3c06650(param_1,local_res18,2);
    if ((char)uVar1 != '\0') {
      *param_2 = local_res18[0];
      return CONCAT71((uint7)(byte)((ushort)local_res18[0] >> 8),1);
    }
  }
  return uVar1 & 0xffffffffffffff00;
}

