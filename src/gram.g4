grammar gram;

topLevel :
        expr EOF
    ;

expr :
    TRUE                          #TrueLit
    | FALSE                       #FalseLit
    | NOT expr                    #NotExpr
    | l=expr AND r=expr           #AndExpr
    | l=expr OR r=expr            #OrExpr
    | OPEN_PAREN expr CLOSE_PAREN #ParenExpr
    ;

TRUE : 'true';
FALSE : 'false';
OR : 'or';
AND : 'and';
NOT : 'not';
CLOSE_PAREN : ')';
OPEN_PAREN : '(';


WS  : [ \t\r\n]+ -> skip ;
