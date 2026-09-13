// image offset 0xA769E0 address 7ff7a3c069e0

void FUN_7ff7a3c069e0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  char local_res18 [16];
  
  cVar1 = FUN_7ff7a3c06a30(param_1,1);
  if (cVar1 != '\0') {
    local_res18[0] = '\0';
    cVar1 = FUN_7ff7a3c06650(param_1,local_res18,1);
    if (cVar1 != '\0') {
      *(bool *)param_2 = local_res18[0] != '\0';
    }
  }
  return;
}

