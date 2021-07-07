% chap1/elastic_scattering.mp -- do not edit, generated automatically by main.tex
input feynmp
require_RCS_revision "1.30";
beginchar(1, 8*28.45274pt#, 5*28.45274pt#, 0);
"feynmf: 1";
LaTeX_unitlength:=28.45274pt;
subgraph (0, 0, w, h);
vinit;
pickup pencircle scaled thin;
vleft (__ie, __oe);
vright (__ip, __op);
vlabel ("$(E_e,\vec {p}_e)$", __ie);
vlabel ("$(E'_e,\vec {p'}_e)$", __oe);
vlabel ("$(E_p,\vec {p}_p)$", __ip);
vlabel ("$(E'_p,\vec {p'}_p)$", __op);
vconnect ("fermion", __ie, __v1, __oe);
vconnect ("photon,label=$q_\mu =(\nu ,,\vec {q})$", __v1, __v2);
vconnect ("fermion", __ip, __v2, __op);
vfreeze;
vdraw;
endsubgraph;
endchar;
% the end.
end.
endinput;
