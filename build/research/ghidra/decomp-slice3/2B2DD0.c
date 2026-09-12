// image offset 0x2B2DD0 address 7ff7a3442dd0

void FUN_7ff7a3442d50(void)

{
  char cVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  undefined *_Dst;
  longlong lVar5;
  undefined *_Dst_00;
  undefined1 local_848 [2076];
  int local_2c;
  
  iVar4 = 0;
  _Dst_00 = &DAT_7ff7ab97b7b0;
  lVar5 = 0;
  _Dst = &DAT_7ff7ab97b7b0;
  do {
    if (*(int *)((longlong)&DAT_7ff7ab97f938 + lVar5) != 0) {
      cVar1 = FUN_7ff7a3398650(0,iVar4,0x88);
      if (cVar1 == '\0') {
        cVar1 = FUN_7ff7a3398650(0,iVar4,0x87);
        if (cVar1 == '\0') {
          memcpy(local_848,
                 &DAT_7ff7ab97c870 +
                 (ulonglong)*(uint *)((longlong)&DAT_7ff7ab97f930 + lVar5) * 0x820 + lVar5,0x820);
          if (local_2c == 0) {
            lVar2 = FUN_7ff7a33981b0(0,iVar4,0x87);
            cVar1 = FUN_7ff7a39c9650();
            if (cVar1 != '\0') {
              cVar1 = FUN_7ff7a39c9710();
              if (cVar1 != '\0') {
                memset(_Dst,0,0x81b);
                FUN_7ff7a3be01b0(_Dst + 0x820);
                memcpy(_Dst_00,local_848,0x81b);
                FUN_7ff7a39c9700(lVar2,_Dst);
                pcVar3 = thunk_FUN_7ff7a334988d;
                *(undefined1 *)(lVar2 + 1) = 0;
                goto LAB_7ff7a3442ef3;
              }
            }
          }
          else {
            lVar2 = FUN_7ff7a33981b0(0,iVar4,0x88);
            cVar1 = FUN_7ff7a39c9650();
            if (cVar1 != '\0') {
              cVar1 = FUN_7ff7a39c9710();
              if (cVar1 != '\0') {
                memset(_Dst,0,0x81b);
                FUN_7ff7a3be01b0(_Dst + 0x820);
                memcpy(_Dst_00,local_848,0x81b);
                FUN_7ff7a39c9700(lVar2,_Dst);
                pcVar3 = FUN_7ff7a339dd70;
LAB_7ff7a3442ef3:
                *(code **)(lVar2 + 0x30) = pcVar3;
                *(code **)(lVar2 + 0x40) = FUN_7ff7a3442fa0;
                *(code **)(lVar2 + 0x38) = FUN_7ff7a3443030;
                FUN_7ff7a39c97e0(lVar2);
                *(int *)((longlong)&DAT_7ff7ab97f938 + lVar5) =
                     *(int *)((longlong)&DAT_7ff7ab97f938 + lVar5) + -1;
                *(uint *)((longlong)&DAT_7ff7ab97f930 + lVar5) =
                     (*(int *)((longlong)&DAT_7ff7ab97f930 + lVar5) + 1U) % 6;
              }
            }
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
    _Dst = _Dst + 0x860;
    _Dst_00 = _Dst_00 + 0x860;
    lVar5 = lVar5 + 0x30cc;
    if (1 < iVar4) {
      return;
    }
  } while( true );
}

