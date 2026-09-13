// image offset 0x701150 address 7ff7a3891150

void FUN_7ff7a3891150(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = 0;
  pcVar3 = &DAT_7ff7affb2238;
  do {
    cVar1 = FUN_7ff7a3919cc0(iVar2);
    if (cVar1 != '\0') {
      cVar1 = FUN_7ff7a39c4640(iVar2);
      if ((cVar1 != '\0') && (*pcVar3 == '\0')) {
        cVar1 = FUN_7ff7a3398650(9,iVar2,0x8b);
        if (cVar1 == '\0') {
          FUN_7ff7a3890d00(iVar2,0);
        }
      }
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x11a0;
  } while (iVar2 < 2);
  return;
}

