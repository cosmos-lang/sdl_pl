% Null
%
% module
% 21
space_21(_o,_o2,_upvals):-_upvals=[_sp,_sp,_sp,_sp,_sp,_img,_sp,_clear],(writeln_(_o),get_(_o,"x",T47),calc(T47+1.0,T48),_y = T48,call_cl(_clear,[]),get_(_sp,"drawImage",T50),_T49 = T50,call_cl(_T49,[_img,0.0,100.0]),get_(_sp,"setRGB",T52),_T51 = T52,call_cl(_T51,[0.0,0.0,0.0]),get_(_sp,"rect",T54),_T53 = T54,get_(_o,"x",T55),call_cl(_T53,[T55,0.0,50.0,50.0]),get_(_sp,"test",T57),_T56 = T57,call_cl(_T56,[_a]),get_(_sp,"refresh",T59),_T58 = T59,call_cl(_T58,[]),writeln_(_sp),writeln_(_y),new(T60),set_(T60,"x",_y,T61),_o2 = T61,true).
% 20
space_20(_key,_upvals):-_upvals=[],(writeln_(_key)).
% 19
space_19(_x,_y,_upvals):-_upvals=[],(writeln_(_x,_y)).
% clear
space_clear(_upvals):-_upvals=[_sp,_sp],(get_(_sp,"setRGBA",T38),_T37 = T38,call_cl(_T37,[255.0,255.0,255.0,255.0]),get_(_sp,"clear",T40),_T39 = T40,call_cl(_T39,[])).
% 18
space_18(_o,_y,_upvals):-_upvals=[],(get_(_o,"name",T25),nb_getval(T25,_y)).
% 17
space_17(_o,_y,_upvals):-_upvals=[],(get_(_o,"name",T24),nb_setval(T24,_y)).
% 16
space_16(_val,_o,_upvals):-_upvals=[_Var,_table],(gensym("var",_x),get_(_table,"concat",T20),_T19 = T20,new(T21),set_(T21,"name",_x,T22),call_cl(_T19,[_Var,T22,_o]),nb_setval(_x,_val)).
% 15
space_15(_a,_upvals):-_upvals=[],(_a = 2.0).
% 14
space_14(_a0,_upvals):-_upvals=[],(sdl_delay(_a0)).
% 13
space_13(_a,_a2,_a3,_upvals):-_upvals=[],(start(_a,_a2,_a3)).
% 12
space_12(_upvals):-_upvals=[],(refresh).
% 11
space_11(_upvals):-_upvals=[],(clear).
% 10
space_10(_upvals):-_upvals=[],(readkey).
% 9
space_9(_upvals):-_upvals=[],(init).
% 8
space_8(_a0,_a1,_a2,_upvals):-_upvals=[],(int(255.0,X12),int(_a2,X11),int(_a1,X10),int(_a0,X9),setRGBA(X9,X10,X11,X12)).
% 7
space_7(_a0,_a1,_a2,_a3,_upvals):-_upvals=[],(int(_a3,X8),int(_a2,X7),int(_a1,X6),int(_a0,X5),setRGBA(X5,X6,X7,X8)).
% 6
space_6(_a0,_a1,_a2,_a3,_upvals):-_upvals=[],(int(_a3,X4),int(_a2,X3),int(_a1,X2),int(_a0,X1),rect(X1,X2,X3,X4)).
% 5
space_5(_a0,_a1,_a2,_upvals):-_upvals=[],(drawImage(_a0,_a1,_a2)).
% 4
space_4(_a0,_a1,_upvals):-_upvals=[],(loadImage(_a0,_a1)).
% 3
space_3(_a0,_a1,_a2,_a3,_upvals):-_upvals=[],(getpixel(_a0,_a1,_a2,_a3)).
% 2
space_2(_a0,_a1,_a2,_a3,_upvals):-_upvals=[],(putpixel(_a0,_a1,_a2,_a3)).
% main
space(X):-new(T1),set_(T1,"putpixel",clos([],space_2),T3),set_(T3,"getpixel",clos([],space_3),T4),set_(T4,"loadImage",clos([],space_4),T5),set_(T5,"drawImage",clos([],space_5),T6),set_(T6,"rect",clos([],space_6),T7),set_(T7,"setRGBA",clos([],space_7),T8),set_(T8,"setRGB",clos([],space_8),T9),set_(T9,"init",clos([],space_9),T10),set_(T10,"readkey",clos([],space_10),T11),set_(T11,"clear",clos([],space_11),T12),set_(T12,"refresh",clos([],space_12),T13),set_(T13,"start",clos([],space_13),T14),set_(T14,"delay",clos([],space_14),T15),set_(T15,"test",clos([],space_15),T2),_sp = T2,writeln_(_sp),ensure_loaded("sdl.pl"),ensure_loaded("callbacks.pl"),creq("mutable",_mutable),creq("table",_table),new(T16),set_(T16,"new",clos([_Var,_table],space_16),T18),set_(T18,"set",clos([],space_17),T23),set_(T23,"get",clos([],space_18),T17),_Var = T17,get_(_Var,"new",T28),_T27 = T28,call_cl(_T27,['[|]'(1.0,'[|]'(2.0,[])),_T26]),_pos = _T26,get_(_Var,"new",T31),_T30 = T31,call_cl(_T30,["right",_T29]),_dir = _T29,get_(_sp,"loadImage",T34),_T33 = T34,call_cl(_T33,["b1.png",_T32]),_img = _T32,get_(_sp,"init",T36),_T35 = T36,call_cl(_T35,[]),writeln_(_img),_clear = clos([_sp,_sp],space_clear),get_(_sp,"start",T42),_T41 = T42,new(T62),set_(T62,"x",10.0,T63),new(T43),set_(T43,"mouseup",clos([],space_19),T45),set_(T45,"keypressed",clos([],space_20),T46),set_(T46,"update",clos([_sp,_sp,_sp,_sp,_sp,_img,_sp,_clear],space_21),T44),call_cl(_T41,[50.0,T44,T63]).