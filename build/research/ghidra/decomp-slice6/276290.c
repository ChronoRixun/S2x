// image offset 0x276290 address 7ff7a3406290

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a3406290(undefined8 param_1,int param_2)

{
  char cVar1;
  
  cVar1 = FUN_7ff7a39c9000(param_1,&DAT_7ff7ab0f485c);
  if (cVar1 != '\0') {
    if ((DAT_7ff7ab0f4858 == 0x96) || (param_2 == 0x1f43)) {
      FUN_7ff7a3405360(DAT_7ff7ab0f4878,0x18,0,&DAT_7ff7ab0f485c);
      DAT_7ff7ab0f4878 = 0xffffffff;
      DAT_7ff7ab0f487c = 0;
      _DAT_7ff7ab0f4854 = 0;
      DAT_7ff7ab0f4850 = 0;
      _DAT_7ff7ab0f485c = 0;
      uRam00007ff7ab0f4864 = 0;
      DAT_7ff7ab0f486c = 0;
      DAT_7ff7ab0f4874 = 0;
      return;
    }
    DAT_7ff7ab0f487c = 1;
  }
  return;
}

