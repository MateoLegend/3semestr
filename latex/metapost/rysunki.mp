outputtemplate:="%j%c.mps";
beginfig(1);

numeric u;
u:=1cm;

pair A,B,C,D,E,G;
A=(0,0);
B=(6u,0);
C=(3u,4u);

D=1/2[B,C];
E=1/2[A,B];

path p,q;
p=A--D;
q=C--E;

draw A--B--C--cycle withpen pencircle scaled 1.5 bp;
draw p withcolor red;

color c;
c=(120/255, 24/255, 100/255);

draw q withcolor c;

draw A withpen pencircle scaled 3bp;
draw B withpen pencircle scaled 3bp;
draw C withpen pencircle scaled 3bp;

draw D withpen pencircle scaled 3bp withcolor red;
draw E withpen pencircle scaled 3bp withcolor red;

G = p intersectionpoint q;
draw G withpen pencircle scaled 3bp withcolor blue;


label.llft(btex $A$ etex, A);
label.lrt(btex $B$ etex, B);
label.top(btex $C$ etex, C);
label.urt(btex $D$ etex, D);
label.bot(btex $E$ etex, E);
label.ulft(btex $G$ etex, G);
% rt, lft, urt, ulft, lrt, llft, top, bot



endfig;

end