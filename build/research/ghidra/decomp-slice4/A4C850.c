// image offset 0xA4C850 address 7ff7a3bdc850

undefined1 FUN_7ff7a3bdc850(longlong param_1,undefined8 param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a3bf44f0(param_2,1,param_1 + 0x10,0x19);
  if (cVar1 != '\0') {
    cVar1 = FUN_7ff7a3bf46c0(param_2,2,param_1 + 0x30);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a3bf43d0(param_2,3,param_1 + 0x38);
      if (cVar1 != '\0') {
        cVar1 = FUN_7ff7a3bdbb10(param_2,4,param_1 + 0x198);
        if (cVar1 != '\0') {
          cVar1 = FUN_7ff7a3bdbfc0(param_2,5,param_1 + 0x1a8);
          if (cVar1 != '\0') {
            cVar1 = FUN_7ff7a3bdbd60(param_2,6,param_1 + 0x1b8);
            if (cVar1 != '\0') {
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

