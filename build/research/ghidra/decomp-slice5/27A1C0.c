// image offset 0x27A1C0 address 7ff7a340a1c0

undefined * FUN_7ff7a340a1c0(int param_1)

{
  undefined *puVar1;
  
  if (((DAT_7ff7ab0ff108 == (undefined *)0x0) ||
      (puVar1 = DAT_7ff7ab0ff108, *(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) &&
     (puVar1 = &DAT_7ff7ab0ffe94, (&DAT_7ff7ab0ffe94)[(longlong)param_1 * 0x2e0] == '\0')) {
    return &DAT_7ff7ab0ffe00;
  }
  return (undefined *)CONCAT71((int7)((ulonglong)puVar1 >> 8),1);
}

