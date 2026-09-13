// image offset 0x274C00 address 7ff7a3404c00

undefined8 FUN_7ff7a3404c00(undefined8 param_1)

{
  char *pcVar1;
  undefined8 uVar2;
  
  pcVar1 = (char *)FUN_7ff7a3261ba0(param_1,0x2e);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    uVar2 = FUN_7ff7a3b94ed0(pcVar1);
    return uVar2;
  }
  return 0;
}

