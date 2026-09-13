// image offset 0xA4C7B0 address 7ff7a3bdc7b0

undefined1 FUN_7ff7a3bdc7b0(longlong param_1,undefined8 param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a3bf44f0(param_2,1,param_1 + 0x10,0x10);
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3bf44f0(param_2,2,param_1 + 0x20,0x100);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a3bf44f0(param_2,3,param_1 + 0x120,0x25);
      if (cVar1 != '\0') {
        cVar1 = FUN_7ff7a3bf4650(param_2,4,param_1 + 0x148);
        if (cVar1 != '\0') {
          return 1;
        }
      }
    }
  }
  return 0;
}

