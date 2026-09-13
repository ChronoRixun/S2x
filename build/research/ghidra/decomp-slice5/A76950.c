// image offset 0xA76950 address 7ff7a3c06950

ulonglong FUN_7ff7a3c06950(undefined8 param_1,longlong param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  ulonglong uVar4;
  uint local_res20 [2];
  
  uVar4 = FUN_7ff7a3c06a30(param_1,0x13);
  if ((char)uVar4 != '\0') {
    local_res20[0] = 0;
    bVar3 = FUN_7ff7a3c07030(param_1,local_res20);
    uVar2 = local_res20[0];
    if ((bVar3 != 0) && (param_2 != 0)) {
      uVar1 = local_res20[0];
      if (*param_3 < local_res20[0]) {
        uVar1 = *param_3;
      }
      bVar3 = FUN_7ff7a3c06650(param_1,param_2,uVar1);
      if (*param_3 < uVar2) {
        FUN_7ff7a3c0e4a0(uVar2);
      }
    }
    *param_3 = uVar2;
    uVar4 = (ulonglong)bVar3;
  }
  return uVar4;
}

