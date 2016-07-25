grammar gram;

topLevel :
        expr EOF
    ;

expr :
    TRUE                          #TrueLit
    | FALSE                       #FalseLit
    | l=expr AND r=expr           #AndExpr
    | l=expr OR r=expr            #OrExpr
    | OPEN_PAREN expr CLOSE_PAREN #ParenExpr
    ;

TRUE : 'true';
FALSE : 'false';
OR : 'or';
AND : 'and';
CLOSE_PAREN : ')';
OPEN_PAREN : ')';


WS  : [ \t\r\n]+ -> skip ;
