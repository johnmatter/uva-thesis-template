% chap1/quasielastic_scattering.mp -- do not edit, generated automatically by main.tex
input feynmp
require_RCS_revision "1.30";
beginchar(1, 8*28.45274pt#, 5*28.45274pt#, 0);
"feynmf: 1";
LaTeX_unitlength:=28.45274pt;
subgraph (0, 0, w, h);
vinit;
pickup pencircle scaled thin;
vleft (__ie, __oe);
vright (__iA, __oAm1, __op);
vlabel ("$(E_e,\vec {p}_e)$", __ie);
vlabel ("$(E'_e,\vec {p'}_e)$", __oe);
vlabel ("$(E_A,\vec {p}_A)$", __iA);
vlabel ("$(E'_p,\vec {p'}_p)$", __op);
vlabel ("$(E_{A-1},\vec {p}_{A-1})$", __oAm1);
vconnect ("fermion", __ie, __v1, __oe);
vconnect ("photon,label=$q_\mu =(\omega ,,\vec {q})$", __v1, __v3);
vconnect ("dbl_plain_arrow", __iA, __v2);
vblob ((16), __v2);
vconnect ("fermion,label=$(E_s,,\vec {p}_p)$", __v2, __v3);
vconnect ("dbl_plain_arrow", __v2, __oAm1);
vconnect ("fermion", __v3, __op);
vfreeze;
vdraw;
endsubgraph;
endchar;
% the end.
end.
endinput;
