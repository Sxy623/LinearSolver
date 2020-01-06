NAME EXAMPLE
ROWS
 N  OBJ
 G  ROW01   
 L  ROW02   
 E  ROW03   
 E  ROW04   
 E  ROW05   
COLUMNS
    COL01     OBJ       1
    COL01     ROW01     3
    COL01     ROW05     5.6
    COL02     ROW01     1
    COL02     ROW02     2
    COL03     ROW02     1.1
    COL03     ROW03     1
    COL04     ROW01     -2
    COL04     ROW04     2.8
    COL05     OBJ       2
    COL05     ROW01     -1
    COL05     ROW05     1
    COL06     ROW03     1
    COL07     ROW04     -1.2
    COL08     OBJ       -1
    COL08     ROW01     -1
    COL08     ROW05     1.9
    MPS_RgROW04  ROW04     -1
    MPS_RgROW05  ROW05     1
RHS
    RHS1      ROW01     2.5
    RHS1      ROW02     2.1
    RHS1      ROW03     4
    RHS1      ROW04     1.8
    RHS1      ROW05     15
BOUNDS
 LO BND1      COL01     2.5
 UP BND1      COL02     4.1
 LO BND1      COL05     0.5
 UP BND1      COL05     4
 UP BND1      COL08     4.3
 UP BND1      MPS_RgROW04  3.2
 UP BND1      MPS_RgROW05  12
ENDATA
