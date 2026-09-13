// image offset 0x372020 address 7ff7a3502020

ulonglong FUN_7ff7a3502020(void)

{
  uint uVar1;
  ulonglong in_RAX;
  longlong *plVar2;
  
  plVar2 = &DAT_7ff7abba5010;
  do {
    if ((*(int *)((longlong)plVar2 + -0x8c) != 0) && (0 < DAT_7ff7abba5b8c)) {
      in_RAX = (ulonglong)DAT_7ff7abba5b88;
      do {
        if ((*(int *)(in_RAX * 0x1ca0 + 0x102c + *plVar2) != 0) &&
           (*(char *)((longlong)(int)in_RAX + -0xa8 + (longlong)plVar2) == '\0')) {
          return CONCAT71((int7)(in_RAX >> 8),1);
        }
        uVar1 = (int)in_RAX + 1;
        in_RAX = (ulonglong)uVar1;
      } while ((int)(uVar1 - DAT_7ff7abba5b88) < DAT_7ff7abba5b8c);
    }
    plVar2 = plVar2 + 0x22;
    if (0x7ff7abba522f < (longlong)plVar2) {
      return in_RAX & 0xffffffffffffff00;
    }
  } while( true );
}

