// image offset 0xA4CBA0 address 7ff7a3bdcba0

undefined1 FUN_7ff7a3bdcba0(longlong param_1,undefined8 param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a3bf3fa0(param_2,1,param_1 + 0x10,0x10);
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3bf3fa0(param_2,2,param_1 + 0x20,0x25);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a3bf3fa0(param_2,3,param_1 + 0x4c,0x19);
      if (cVar1 != '\0') {
        cVar1 = FUN_7ff7a3bf4020(param_2,4,*(undefined4 *)(param_1 + 0x48));
        if (cVar1 != '\0') {
          return 1;
        }
      }
    }
  }
  return 0;
}

