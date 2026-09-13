// image offset 0x273650 address 7ff7a3403650

void FUN_7ff7a3403650(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = FUN_7ff7a3631500();
  FUN_7ff7a3241fd0(DAT_7ff7b13c6b48,0);
  FUN_7ff7a3630be0("menu_STORE");
  if ((DAT_7ff7ab0ff158 != 0) && (0 < *(int *)(DAT_7ff7ab0ff158 + 0x10))) {
    iVar3 = 0;
    do {
      cVar1 = FUN_7ff7a3919d60(iVar3);
      if (cVar1 != '\0') {
        FUN_7ff7a38f6310(iVar3);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
  }
  FUN_7ff7a3401b30(uVar2);
  return;
}

