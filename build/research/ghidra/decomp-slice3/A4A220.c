// image offset 0xA4A220 address 7ff7a3bda220

longlong FUN_7ff7a3bda220(longlong param_1,uint param_2)

{
  _eh_vector_destructor_iterator_((void *)(param_1 + -0x240),0x38,10,FUN_7ff7a339ba80);
  FUN_7ff7a3bcb570(param_1 + -0x340);
  FUN_7ff7a3bbc060(param_1 + -0x350);
  FUN_7ff7a3c04d10(param_1);
  if ((param_2 & 1) != 0) {
    if ((param_2 & 4) == 0) {
      FUN_7ff7a3c05240(param_1 + -0x360);
    }
    else {
      FUN_7ff7a31a2b10(param_1 + -0x360,0x370);
    }
  }
  return param_1 + -0x360;
}

