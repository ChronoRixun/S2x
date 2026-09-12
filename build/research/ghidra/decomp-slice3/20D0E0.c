// image offset 0x20D0E0 address 7ff7a339d0e0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a339d0e0(longlong param_1)

{
  longlong lVar1;
  undefined4 *puVar2;
  longlong lVar3;
  undefined1 auStack_3a8 [32];
  undefined1 local_388 [16];
  undefined1 local_378 [16];
  undefined1 local_368 [256];
  undefined1 local_268 [576];
  undefined1 local_28 [16];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_3a8;
  *(undefined8 *)(param_1 + 0x15958) = 0;
  *(undefined1 *)(param_1 + 0x15964) = 0;
  *(undefined4 *)(param_1 + 0x15960) = 0;
  *(undefined4 *)(param_1 + 0x15954) = 0;
  memset((void *)(param_1 + 88000),0,400);
  *(undefined4 *)(param_1 + 0x15950) = 0;
  lVar1 = FUN_7ff7a3bd9fb0(local_388,1);
  lVar3 = 100;
  puVar2 = (undefined4 *)(param_1 + 0x358);
  do {
    FUN_7ff7a339b720(puVar2 + -0xd6,lVar1);
    *(undefined1 *)(puVar2 + -2) = *(undefined1 *)(lVar1 + 0x350);
    *puVar2 = *(undefined4 *)(lVar1 + 0x358);
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)(lVar1 + 0x35c);
    puVar2 = puVar2 + 0xdc;
    lVar3 = lVar3 + -1;
  } while (lVar3 != 0);
  _eh_vector_destructor_iterator_(local_268,0x38,10,FUN_7ff7a339ba80);
  FUN_7ff7a3bcb570(local_368);
  FUN_7ff7a3bbc060(local_378);
  FUN_7ff7a3c04d10(local_28);
  return;
}

