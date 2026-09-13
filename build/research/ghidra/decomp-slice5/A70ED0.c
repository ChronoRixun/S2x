// image offset 0xA70ED0 address 7ff7a3c00ed0

undefined8 FUN_7ff7a3c00ed0(longlong param_1,undefined8 param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a3bf46c0(param_2,1,param_1 + 0x10);
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3bf44f0(param_2,2,param_1 + 0x18,0x14);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a3bf4290(param_2,3,param_1 + 0x2c,0x1000,param_1 + 0x102c);
      if (cVar1 != '\0') {
        cVar1 = FUN_7ff7a3bf4290(param_2,4,param_1 + 0x1030,0x800,param_1 + 0x1830);
        if (cVar1 != '\0') {
          cVar1 = FUN_7ff7a3bf4290(param_2,5,param_1 + 0x1834,0x400,param_1 + 0x1c34);
          if (cVar1 != '\0') {
            cVar1 = FUN_7ff7a3bf4290(param_2,6,param_1 + 0x1c38,0x40,param_1 + 0x1c78);
            if (cVar1 != '\0') {
              cVar1 = FUN_7ff7a3bf46c0(param_2,7,param_1 + 0x1c80);
              if (cVar1 != '\0') {
                cVar1 = FUN_7ff7a3bf4650(param_2,8,param_1 + 0x1c88);
                if (cVar1 != '\0') {
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

