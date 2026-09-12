// image offset 0x278400 address 7ff7a3408400

longlong FUN_7ff7a3408400(void)

{
  uint7 uVar1;
  
  uVar1 = (uint7)((ulonglong)DAT_7ff7ab0ff108 >> 8);
  if (((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) &&
     (DAT_7ff7ab2938a8 == '\0')) {
    return (ulonglong)uVar1 << 8;
  }
  return CONCAT71(uVar1,1);
}

