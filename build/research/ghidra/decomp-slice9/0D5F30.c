// image offset 0xD5F30 address 7ff7a3265f30

void FUN_7ff7a3265f30(int param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  longlong lVar7;

  cVar1 = FUN_7ff7a340a210(param_1);
  if (cVar1 != '\0') {
    iVar3 = FUN_7ff7a325f390(param_1);
    if ((&DAT_7ff7a4cc2868)[(longlong)iVar3 * 0x15d70 + (longlong)param_1 * 0x41920] != '\0') {
      iVar3 = FUN_7ff7a325f390(param_1);
      iVar4 = FUN_7ff7a3409780(param_1,1);
      uVar5 = FUN_7ff7a3819900(DAT_7ff7ad7912d4);
      FUN_7ff7a331e9e0(param_1,uVar5,iVar4,0);
      uVar5 = FUN_7ff7a3819900(DAT_7ff7ad790fbc);
      iVar6 = FUN_7ff7a331de50(param_1,uVar5,0);
      if (iVar4 < iVar6) {
        uVar5 = FUN_7ff7a3819900(DAT_7ff7ad790fbc);
        FUN_7ff7a331e9e0(param_1,uVar5,iVar4,0);
      }
      iVar4 = FUN_7ff7a3409780(param_1,8);
      iVar6 = FUN_7ff7a3409780(param_1,0xc);
      if ((iVar4 < 1) || (iVar6 < 1)) {
        cVar1 = '\0';
      }
      else {
        cVar1 = '\x01';
      }
      uVar5 = FUN_7ff7a3819900(DAT_7ff7ad791334);
      cVar2 = FUN_7ff7a331db90(param_1,uVar5,0);
      if (cVar2 != cVar1) {
        uVar5 = FUN_7ff7a3819900(DAT_7ff7ad791334);
        FUN_7ff7a331e790(param_1,uVar5,cVar1,0);
      }
      FUN_7ff7a3263720(param_1);
      lVar7 = (longlong)iVar3 * 0x15d70 + (longlong)param_1 * 0x41920;
      *(uint *)(&DAT_7ff7a4cc0100 + lVar7) = *(uint *)(&DAT_7ff7a4cc0100 + lVar7) | 1;
      (&DAT_7ff7a4cc0105)[lVar7] = 1;
      iVar3 = FUN_7ff7a39e55c0();
      if (iVar3 == 1) {
        (&DAT_7ff7a4cc0104)[lVar7] = 1;
      }
    }
  }
  return;
}
