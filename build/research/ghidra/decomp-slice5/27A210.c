// image offset 0x27A210 address 7ff7a340a210

ulonglong FUN_7ff7a340a210(int param_1)

{
  ulonglong uVar1;
  
  if ((DAT_7ff7ab0ff108 == 0) || (uVar1 = DAT_7ff7ab0ff108, *(int *)(DAT_7ff7ab0ff108 + 0x10) != 0))
  {
    uVar1 = (longlong)param_1 * 0x2e0;
    if (((&DAT_7ff7ab0ffe94)[uVar1] == '\0') ||
       (uVar1 = (longlong)param_1 * 0xc8438, (&DAT_7ff7ab1c85a8)[uVar1] == '\0')) {
      return uVar1 & 0xffffffffffffff00;
    }
  }
  return CONCAT71((int7)(uVar1 >> 8),1);
}

