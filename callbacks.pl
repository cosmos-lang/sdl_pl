
%start(Cl) :- call_cl(Cl).
%update(X,Y):-Y=X.
start(T1,T,Start) :- get_(T,"update",Cl),writeln(Cl),%call_cl(Cl,[1,Y1]),writeln(Y1),assert(update(X,Y):-(Y=X,writeln(Y))),update(1,1),
	assert(update(X,Y):-call_cl(Cl,[X,Y])),
	assert(mouseUp(X):-true),
	assert(keyDown(X):-true),
	sdl_start(T1,Start).