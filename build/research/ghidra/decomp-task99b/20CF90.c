// image offset 0x20CF90 address 7ff7a339cf90

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a339cf90(longlong param_1)

{
  undefined1 auStackY_308 [32];
  undefined **local_2c8;
  undefined *local_2c0;
  undefined1 local_2b8 [88];
  undefined1 local_260 [560];
  undefined **local_30;
  undefined4 local_28;
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStackY_308;
  *(undefined4 *)(param_1 + 0x10b30) = 0;
  *(undefined1 *)(param_1 + 0x10b34) = 0;
  memset((void *)(param_1 + 68000),0,400);
  memset(&local_2c8,0,0x2a8);
  local_2c0 = &DAT_7ff7a3cdb2d0;
  local_30 = &PTR_FUN_7ff7a3ccfa28;
  local_28 = 0;
  FUN_7ff7a3bd87e0(&local_2c8,0);
  local_2c8 = &PTR_FUN_7ff7a3cdb298;
  *(undefined ***)(local_2b8 + (longlong)*(int *)(local_2c0 + 4) + -8) = &PTR_FUN_7ff7a3cdb2c8;
  _eh_vector_vbase_constructor_iterator_(local_260,0x38,10,FUN_7ff7a3bd85a0,FUN_7ff7a339bc20);
  FUN_7ff7a339b1b0(param_1,100,&local_2c8);
  _eh_vector_destructor_iterator_(local_260,0x38,10,FUN_7ff7a339bc20);
  FUN_7ff7a3bbc060(local_2b8);
  FUN_7ff7a3c04d10(&local_30);
  return;
}

